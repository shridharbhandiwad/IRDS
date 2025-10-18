# Track Visualization Features - Architecture Diagram

## System Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                         USER INTERACTION                         │
│                                                                  │
│  Right-click on Track → Context Menu appears                    │
│                                                                  │
│  ┌──────────────────────────────────────────────────┐           │
│  │  🎯 Toggle Focus (Tooltip Always On)             │           │
│  │  ─────────────────────────────────────────────   │           │
│  │  📍 Toggle History (Max 50)                      │           │
│  │  ✨ Toggle Highlight (Larger Size)               │           │
│  │  ─────────────────────────────────────────────   │           │
│  │  🖼️ Load Track Image                             │           │
│  │  ─────────────────────────────────────────────   │           │
│  │  🗑️ Delete Track                                 │           │
│  └──────────────────────────────────────────────────┘           │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│                      EVENT HANDLERS                              │
│                  (MapDisplay/ctracklayer.cpp)                    │
│                                                                  │
│  onFocusTrack()      → Toggle focus state, center map           │
│  onHighlightTrack()  → Toggle highlight state                   │
│  onDeleteTrack()     → Delete track permanently                 │
│  onToggleHistory()   → Toggle history trail [existing]          │
│  onLoadTrackImage()  → Load image [stub]                        │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│                    DATA MANAGEMENT                               │
│                    (cdatawarehouse.cpp)                          │
│                                                                  │
│  focusTrack(id)           → Set isFocused = true               │
│  unfocusAllTracks()       → Clear all focus states              │
│  highlightTrack(id, bool) → Set isHighlighted = state          │
│  deleteTrack(id)          → Remove from _m_listTrackInfo       │
│  getFocusedTrackId()      → Return focused track ID or -1      │
│                                                                  │
│  Data Structure: QHash<int, stTrackDisplayInfo>                 │
│  ├─ Track ID → Track Info mapping                               │
│  └─ Persistent across updates                                   │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│                    DATA STRUCTURES                               │
│                    (globalstructs.h)                             │
│                                                                  │
│  struct stTrackDisplayInfo {                                    │
│      int nTrkId;                                                │
│      double lat, lon, alt;                                      │
│      double heading, velocity;          ← Used for vector       │
│      int nTrackIden;                                            │
│      bool showHistory;                  [existing]              │
│      bool isHighlighted;                ← NEW                   │
│      bool isFocused;                    ← NEW                   │
│      QList<stTrackHistoryPoint> historyPoints;                  │
│  };                                                              │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│                   RENDERING PIPELINE                             │
│              (MapDisplay/ctracklayer.cpp::paint())               │
│                                                                  │
│  For each track in getTrackList():                              │
│                                                                  │
│  1. Determine State                                             │
│     ├─ bool isHovered = (trackId == hoveredId)                 │
│     ├─ bool isHighlighted = track.isHighlighted                │
│     └─ bool isFocused = track.isFocused                         │
│                                                                  │
│  2. Calculate Size Multiplier                                   │
│     ├─ Normal:      1.0x                                        │
│     ├─ Highlighted: 1.8x                                        │
│     └─ Focused:     2.0x                                        │
│                                                                  │
│  3. Draw Visual Effects                                         │
│     ├─ Focused:     Pulsing circles (15-25px)                   │
│     ├─ Highlighted: Static rings (12px, 14px)                   │
│     └─ Hovered:     Subtle rings (10px, 12px)                   │
│                                                                  │
│  4. Draw Core Elements                                          │
│     ├─ Core dot: 4px × sizeMultiplier                           │
│     ├─ Velocity vector:                                         │
│     │   └─ Length = velocity × 2.0 px/m/s (clamped 5-50px)     │
│     │   └─ Width = 2px × sizeMultiplier                         │
│     │   └─ Arrowhead at tip                                     │
│     └─ Label: scaled font (11pt or 13pt bold)                   │
│                                                                  │
│  5. Draw History Trail (if enabled)                             │
│     └─ [Existing functionality]                                 │
│                                                                  │
│  6. Draw Tooltips                                               │
│     ├─ Focused track: Always visible at track position          │
│     └─ Hovered track: At mouse position (if not focused)        │
└─────────────────────────────────────────────────────────────────┘
```

## Data Flow for Each Feature

### 1. Speed Vector Calculation

```
Track velocity data (m/s)
        ↓
vectorLength = velocity × 2.0
        ↓
Clamp: max(5, min(50, vectorLength))
        ↓
Calculate endpoint: 
  x = cos(heading) × vectorLength
  y = sin(heading) × vectorLength
        ↓
Draw line + arrowhead
```

### 2. Highlight Track Flow

```
Right-click → "Toggle Highlight"
        ↓
onHighlightTrack()
        ↓
Read current state: track.isHighlighted
        ↓
highlightTrack(id, !currentState)
        ↓
Update stTrackDisplayInfo.isHighlighted
        ↓
update() → Redraw canvas
        ↓
Paint detects isHighlighted = true
        ↓
Apply 1.8x multiplier + rings
```

### 3. Focus Track Flow

```
Right-click → "Toggle Focus"
        ↓
onFocusTrack()
        ↓
Check: getFocusedTrackId() == clickedId?
        ↓
├─ YES: unfocusAllTracks()
│       └─ Clear isFocused for all
│
└─ NO: focusTrack(clickedId)
       ├─ unfocusAllTracks() first
       ├─ Set isFocused = true for track
       ├─ Set _m_nFocusedTrackId = clickedId
       └─ Center map on track
        ↓
update() → Redraw canvas
        ↓
Paint detects isFocused = true
        ↓
├─ Apply 2.0x multiplier + pulsing rings
└─ Draw tooltip at track position (not mouse)
```

### 4. Delete Track Flow

```
Right-click → "Delete Track"
        ↓
onDeleteTrack()
        ↓
deleteTrack(id)
        ↓
├─ Remove from _m_listTrackInfo
└─ If id == _m_nFocusedTrackId:
    └─ Set _m_nFocusedTrackId = -1
        ↓
update() → Redraw canvas
        ↓
Track no longer in list → not rendered
```

## State Management

```
┌─────────────────────────────────────────────┐
│         Track State Combinations            │
├─────────────────────────────────────────────┤
│                                             │
│  Normal:    ○  Default appearance           │
│                                             │
│  Hovered:   ◎  Subtle rings + cursor change │
│                                             │
│  Highlight: ◉  1.8x size + bright rings     │
│                                             │
│  Focused:   ⦿  2.0x size + pulsing + tooltip│
│                                             │
│  Highlight + Focused: Focus visuals take    │
│                       precedence (2.0x)     │
│                                             │
└─────────────────────────────────────────────┘
```

## Visual Elements by State

```
┌──────────────┬──────────┬────────────┬─────────┐
│   Element    │  Normal  │ Highlighted│ Focused │
├──────────────┼──────────┼────────────┼─────────┤
│ Core Dot     │  4px     │  7.2px     │  8px    │
│ Vector Width │  2px     │  3.6px     │  4px    │
│ Label Font   │  11pt    │  13pt Bold │ 13pt B. │
│ Rings        │  None    │  12px,14px │ 15-25px │
│ Animation    │  Blip    │  Blip      │ Pulse   │
│ Tooltip      │ On hover │  On hover  │ Always  │
└──────────────┴──────────┴────────────┴─────────┘
```

## Velocity Vector Visual

```
          ▲ Arrowhead (4-8px, scales with track)
          │
          │  Vector length = velocity × 2px/m/s
          │  (Minimum: 5px, Maximum: 50px)
          │
          │  Width = 2-4px (scales with track state)
          │
          ● Track core dot (4-8px)
          
Example speeds:
  10 m/s  →  20px vector
  20 m/s  →  40px vector
  35 m/s  →  50px vector (capped)
```

## Component Interaction Diagram

```
┌───────────────┐      ┌──────────────────┐      ┌─────────────┐
│               │      │                  │      │             │
│  Track Layer  │◄────►│  Data Warehouse  │◄────►│    Tracks   │
│  (View)       │      │  (Model)         │      │   (Data)    │
│               │      │                  │      │             │
└───────┬───────┘      └────────┬─────────┘      └─────────────┘
        │                       │
        │ Rendering             │ State Management
        │                       │
        ├─ paint()              ├─ focusTrack()
        ├─ drawTooltip()        ├─ highlightTrack()
        ├─ eventFilter()        ├─ deleteTrack()
        └─ context menu         └─ getTrackList()
```

## Animation Timeline

```
Frame:    0    5    10   15   19   0    5    10
          │    │    │    │    │    │    │    │
Blip:     ●    ◉    ○    ·    ·    ●    ◉    ○
Radius:   4    12   20   28   36   4    12   20
Alpha:    255  191  128  64   0    255  191  128

Focused Track Pulse:
Frame:    0    5    10   15   19   0    5    10
          │    │    │    │    │    │    │    │
Pulse1:   15   20   25   20   15   15   20   25
Pulse2:   18   23   28   23   18   18   23   28
```

## Performance Metrics

```
Per Frame (60 FPS target):
├─ Track detection: O(n) where n = number of tracks
├─ State evaluation: O(1) per track
├─ Vector calculation: O(1) per track
├─ Tooltip rendering: O(1) (max 2: hovered + focused)
└─ Total complexity: O(n) - Linear with track count

Memory footprint per track:
├─ Base structure: ~200 bytes
├─ Added flags: 2 bytes (bool × 2)
├─ History points: ~32 bytes × history_limit
└─ Total overhead: ~2 bytes per track (negligible)
```

---

## Key Design Decisions

1. **Single Focus:** Only one track can be focused at a time
   - Rationale: Prevents tooltip clutter
   - Alternative considered: Multiple focus with stacked tooltips

2. **Size Multipliers:** Discrete levels (1.0x, 1.8x, 2.0x)
   - Rationale: Clear visual hierarchy
   - Alternative considered: Continuous scaling

3. **Vector Clamping:** 5-50px range
   - Rationale: Maintains visibility and prevents overlap
   - Alternative considered: Logarithmic scaling

4. **Tooltip Position:** Track position for focused, mouse for hovered
   - Rationale: Focused tooltip should move with track
   - Alternative considered: Fixed screen position

5. **State Persistence:** Survives track data updates
   - Rationale: User-set states should not reset
   - Implementation: Check existing track before overwriting

---

All components work together to provide a cohesive, intuitive track visualization system! 🎯
