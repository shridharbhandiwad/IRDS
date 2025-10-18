# Track Visualization Features Implementation

## Overview
This document describes the new track visualization features implemented for the radar display system.

## Implemented Features

### 1. Speed Vector (Proportional to Velocity)
**Previous Behavior:** The heading line on each track was a fixed length (10 pixels).

**New Behavior:** 
- The velocity vector length is now proportional to the track's speed
- Scale: 1 m/s = 2 pixels (configurable in code)
- Minimum length: 5 pixels (for visibility at low speeds)
- Maximum length: 50 pixels (to prevent excessive vector lengths)
- The vector includes an arrowhead at the tip to clearly indicate direction
- Vector width scales with track size (larger for highlighted/focused tracks)

**Implementation Location:** `MapDisplay/ctracklayer.cpp` lines ~594-624

### 2. Highlight Functionality
**Purpose:** Make specific tracks more prominent without focusing on them.

**Features:**
- Right-click context menu: "✨ Toggle Highlight (Larger Size)"
- Highlighted tracks are displayed 80% larger (1.8x size multiplier)
- Bright ring around the track (colored based on track identity)
- Larger track label font (13pt bold)
- Thicker velocity vector
- Toggle on/off functionality - can be applied to multiple tracks

**Visual Effects:**
- Primary colored ring (12px radius)
- White outer ring (14px radius)
- Larger core dot and velocity vector

**Implementation Location:** 
- Data structure: `globalstructs.h` - added `isHighlighted` field
- Data management: `cdatawarehouse.cpp` - `highlightTrack()` method
- Visualization: `MapDisplay/ctracklayer.cpp` - paint() method

### 3. Delete Track Functionality
**Purpose:** Remove unwanted tracks from the display.

**Features:**
- Right-click context menu: "🗑️ Delete Track"
- Permanently removes track from the data warehouse
- Automatically unfocuses the track if it was focused
- Immediate visual update

**Implementation Location:**
- Data management: `cdatawarehouse.cpp` - `deleteTrack()` method
- UI handler: `MapDisplay/ctracklayer.cpp` - `onDeleteTrack()` method

### 4. Focus Track (Persistent Tooltip)
**Purpose:** Keep detailed information visible for a specific track while it moves.

**Features:**
- Right-click context menu: "🎯 Toggle Focus (Tooltip Always On)"
- Only one track can be focused at a time
- Focused track displays:
  - Persistent tooltip that moves with the track position
  - Pulsing circles animation (15-25px radius)
  - Bright cyan and white rings
  - 2x size multiplier (largest of all states)
  - Bold 13pt font for label
- Toggle functionality: clicking again unfocuses the track
- Automatically centers the map on the track when focused

**Visual Effects:**
- Animated pulsing circles (cyan and white)
- Largest track representation (2.0x size)
- Tooltip always visible and follows track position
- Tooltip positioned relative to track location (not mouse)

**Implementation Location:**
- Data structure: `globalstructs.h` - added `isFocused` field
- Data management: `cdatawarehouse.cpp` - `focusTrack()`, `unfocusAllTracks()`, `getFocusedTrackId()` methods
- Visualization: `MapDisplay/ctracklayer.cpp` - paint() method with special handling for focused tracks

## Context Menu
The track context menu (accessed via right-click) now includes:
1. 🎯 Toggle Focus (Tooltip Always On)
2. 📍 Toggle History (Max N) - *existing feature*
3. ✨ Toggle Highlight (Larger Size)
4. 🖼️ Load Track Image - *existing feature*
5. 🗑️ Delete Track

## Track State Priority
When multiple states are active:
1. **Focused** - Takes precedence in size (2.0x) and visual effects
2. **Highlighted** - Second priority (1.8x size) if not focused
3. **Hovered** - Subtle effect, doesn't affect focused/highlighted states

## Data Structure Changes

### `globalstructs.h` - `stTrackDisplayInfo`
Added fields:
- `bool isHighlighted` - Flag for highlighting track
- `bool isFocused` - Flag for focused track (always show tooltip)

### `cdatawarehouse.h/cpp`
Added methods:
- `void deleteTrack(int trackId)` - Remove track from display
- `void highlightTrack(int trackId, bool highlight)` - Toggle track highlighting
- `void focusTrack(int trackId)` - Focus on a specific track
- `void unfocusAllTracks()` - Clear all focused tracks
- `int getFocusedTrackId() const` - Get currently focused track ID

Added member:
- `int _m_nFocusedTrackId` - Tracks the currently focused track (-1 if none)

## Technical Details

### Velocity Vector Calculation
```cpp
double velocityScale = 2.0; // pixels per m/s
double vectorLength = track.velocity * velocityScale;

// Clamp for visibility
if (vectorLength < 5) vectorLength = 5;
if (vectorLength > 50) vectorLength = 50;
```

### Size Multipliers
- Normal: 1.0x
- Highlighted: 1.8x
- Focused: 2.0x

### Animation
- Focused tracks: Pulsing effect using `nAnimFrame % 10` for radius variation
- Standard animation frame: 0-19, updates at ~10 FPS (150ms intervals)

## Usage Examples

### To highlight a track:
1. Right-click on the track
2. Select "✨ Toggle Highlight (Larger Size)"
3. Track becomes larger and more prominent
4. Click again to remove highlight

### To focus on a track:
1. Right-click on the track
2. Select "🎯 Toggle Focus (Tooltip Always On)"
3. Track tooltip stays visible and follows the track
4. Map centers on the track
5. Click again to unfocus

### To delete a track:
1. Right-click on the track
2. Select "🗑️ Delete Track"
3. Track is permanently removed

## Notes
- All features work together seamlessly
- Focused tracks show their tooltip even when hovered tracks would normally show theirs
- The velocity vector now provides immediate visual feedback about track speed
- Highlight and focus states can coexist (focus takes visual precedence)
