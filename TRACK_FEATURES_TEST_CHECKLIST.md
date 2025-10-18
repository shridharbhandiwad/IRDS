# Track Visualization Features - Test Checklist

## Feature 1: Speed Vector (Proportional to Velocity)
- [ ] Verify that track velocity vectors are no longer fixed length
- [ ] Confirm that faster tracks show longer velocity vectors
- [ ] Check that slower tracks show shorter velocity vectors (minimum 5px)
- [ ] Verify that extremely fast tracks are clamped at maximum 50px
- [ ] Confirm that velocity vector has an arrowhead indicating direction
- [ ] Check that velocity vector scales with track size (highlighted/focused tracks have thicker vectors)

**Expected Behavior:**
- Track 1: velocity = 20 m/s → vector length ≈ 40 pixels
- Track 2: velocity = 20 m/s → vector length ≈ 40 pixels
- Track 3: velocity = 35 m/s → vector length ≈ 50 pixels (clamped at max)
- Vector width: 2px normal, scales with highlight/focus

## Feature 2: Highlight Functionality
- [ ] Right-click on a track and select "✨ Toggle Highlight (Larger Size)"
- [ ] Verify track becomes larger (1.8x size)
- [ ] Confirm bright ring appears around the track
- [ ] Check that track label font increases to 13pt bold
- [ ] Verify velocity vector is thicker
- [ ] Toggle highlight off and confirm track returns to normal size
- [ ] Test highlighting multiple tracks simultaneously
- [ ] Verify highlighted tracks remain highlighted after map zoom/pan

**Visual Indicators:**
- Colored ring at 12px radius (track identity color)
- White outer ring at 14px radius
- Core dot: 7.2px radius (4 × 1.8)
- Velocity vector width: 3.6px (2 × 1.8)

## Feature 3: Delete Track Functionality
- [ ] Right-click on a track and select "🗑️ Delete Track"
- [ ] Verify track is immediately removed from display
- [ ] Confirm track does not reappear on subsequent updates
- [ ] Test deleting a focused track - verify focus is cleared
- [ ] Test deleting a highlighted track
- [ ] Test deleting a track with history enabled
- [ ] Check console for "Track deleted: [ID]" message

**Expected Behavior:**
- Track removed from `_m_listTrackInfo` hash
- If focused, `_m_nFocusedTrackId` set to -1
- Canvas refreshes immediately

## Feature 4: Focus Track (Persistent Tooltip)
- [ ] Right-click on a track and select "🎯 Toggle Focus (Tooltip Always On)"
- [ ] Verify tooltip appears and stays visible
- [ ] Confirm tooltip follows the track as it moves
- [ ] Check that map centers on the track
- [ ] Verify pulsing animation around focused track
- [ ] Confirm track is largest (2.0x size multiplier)
- [ ] Test focusing on a different track - verify first track unfocuses
- [ ] Toggle focus off - verify tooltip disappears
- [ ] Test focusing while hovering over same track - verify focused tooltip takes precedence

**Visual Indicators:**
- Animated pulsing circles: 15-25px radius (cyan)
- White outer ring: 18-28px radius
- Core dot: 8px radius (4 × 2.0)
- Velocity vector width: 4px (2 × 2.0)
- Tooltip positioned relative to track location
- Bold 13pt font for track label

## Combined State Tests
- [ ] Test: Hover over normal track → verify subtle highlight
- [ ] Test: Hover over highlighted track → verify highlight + hover effects
- [ ] Test: Hover over focused track → verify only one tooltip shown (focused)
- [ ] Test: Focus + Highlight same track → verify focus visual takes precedence
- [ ] Test: History + Highlight → verify both work together
- [ ] Test: History + Focus → verify both work together
- [ ] Test: Delete highlighted track → verify cleanup
- [ ] Test: Delete focused track → verify focus cleared

## Context Menu
- [ ] Right-click on track opens context menu
- [ ] Menu items are properly labeled with emojis
- [ ] Menu has proper styling (rounded corners, gradient on hover)
- [ ] All menu items are clickable and functional
- [ ] Menu closes after selection

**Menu Structure:**
1. 🎯 Toggle Focus (Tooltip Always On)
2. --- separator ---
3. 📍 Toggle History (Max N)
4. ✨ Toggle Highlight (Larger Size)
5. --- separator ---
6. 🖼️ Load Track Image
7. --- separator ---
8. 🗑️ Delete Track

## Performance Tests
- [ ] Verify no performance degradation with multiple highlighted tracks
- [ ] Check animation smoothness on focused track
- [ ] Test with all three default tracks visible
- [ ] Verify no memory leaks when deleting tracks

## Edge Cases
- [ ] Test with zoom in (high pixelPerDegree)
- [ ] Test with zoom out (low pixelPerDegree)
- [ ] Test deleting all tracks
- [ ] Test rapidly toggling focus on different tracks
- [ ] Test context menu on track at screen edge

## Console Output Verification
Expected debug messages:
- "Focused on track [ID]" - when focusing
- "Track unfocused: [ID]" - when unfocusing
- "Track highlight toggled: [ID]" - when highlighting
- "Track deleted: [ID]" - when deleting
- "Toggle history for track [ID]" - when toggling history

## Code Quality Checks
- [x] No compilation errors
- [x] No linter errors
- [x] Proper memory management (destructors, cleanup)
- [x] Thread-safe singleton pattern in CDataWarehouse
- [x] Consistent coding style
- [x] Proper use of Qt math functions (qDegreesToRadians)

## Visual Regression
Before/After comparison:
- **Before:** Fixed 10px velocity line, no highlight, no focus, no delete
- **After:** Proportional velocity vector with arrow, highlight (1.8x), focus (2.0x with tooltip), delete capability

All features implemented successfully! ✅
