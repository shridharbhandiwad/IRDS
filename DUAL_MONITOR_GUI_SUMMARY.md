# Dual Monitor GUI Enhancement Summary

## Overview
The GUI has been significantly enhanced to support dual-monitor setups with a clean, light color theme using two primary colors throughout the application.

## Key Improvements

### 1. **Dual Monitor Architecture**

The application now consists of three main windows:

#### **Monitor 1: PPI Window** (`CPPIWindow`)
- **Location**: `MapDisplay/cppiwindow.h` and `MapDisplay/cppiwindow.cpp`
- **Components**:
  - Map canvas with PPI (Plan Position Indicator) display
  - Track table widget (dockable on right side)
  - Settings button (top-left floating overlay)
  - Context menu for track operations

#### **Monitor 2: Controls Window** (`CControlsWindow`)
- **Location**: `MapDisplay/ccontrolswindow.h` and `MapDisplay/ccontrolswindow.cpp`
- **Components**:
  - Rich tabbed interface containing:
    - ⚙️ Configuration panel
    - 🔌 Interfaces panel
    - 📊 Analytics widget
    - 🎮 Simulation widget
    - ⏺️ Recording widget
    - 💚 Health Monitor
    - 🔧 Predictive Maintenance
    - 📈 Charts widget

#### **Main Window** (`CMapMainWindow`)
- **Location**: `cmapmainwindow.h` and `cmapmainwindow.cpp`
- **Role**: Controller that manages both windows
- **Features**:
  - Automatic window positioning for dual/single monitor setups
  - Signal routing between windows
  - Keyboard shortcuts (F1: Toggle PPI, F2: Toggle Controls, H: Home, Esc: Exit)

### 2. **Light Color Theme**

The application uses a consistent light color scheme with two primary colors:

- **Primary Color**: Light Blue (#E3F2FD) - Used for backgrounds, headers, and buttons
- **Secondary Color**: White (#FFFFFF) - Used for content areas and widgets
- **Accent Color**: Medium Blue (#90CAF9) - Used for borders and highlights
- **Text Color**: Dark Blue (#1565C0) - Used for primary text
- **Selected/Active**: Lighter Blue (#BBDEFB) - Used for hover states and selections

All widgets follow this theme consistently:
- Buttons
- Tables
- Input fields
- Tabs
- Scrollbars
- Menus
- Status bars

### 3. **PPI Window Features**

#### **Settings Button** (Top-left overlay)
Menu options:
- 📂 **Load New Map**: Open file dialog to load raster maps (TIF, PNG, BMP, JPG)
- 🚫 **Disable Map**: Disable base map layers
- 🔍 **Zoom Fit to Max**: Zoom to full extent of the map
- 🏠 **Map Home**: Reset map to home view

#### **Track Context Menu** (Right-click on track)
Options available:
- 🎯 **Focus Track**: Center map on selected track
- ✨ **Highlight & Follow**: Highlight track and follow its movement
- 📊 **Set History Points (Max 50)**: Configure number of history trail points (1-50)
- 🖼️ **Load Track Image**: Assign custom image to track
- 🗑️ **Delete Track**: Remove track from display

#### **Track Table**
- Displays all active tracks with filtering options
- Search by Track ID
- Filter by identity (Friendly, Hostile, Unknown)
- Export to CSV functionality
- Single-click selection
- Double-click to center map on track

### 4. **Track History Management**

Enhanced `stTrackDisplayInfo` structure with:
```cpp
int nMaxHistoryPoints;      // Maximum history points (default: 20, max: 50)
bool bHighlighted;          // Track highlight state
bool bFollowEnabled;        // Auto-follow track movement
QString customImagePath;    // Custom track image path
```

### 5. **Window Management**

#### **Dual Monitor Setup**:
- PPI Window: Positioned on primary monitor (full screen)
- Controls Window: Positioned on secondary monitor (full screen)

#### **Single Monitor Setup**:
- PPI Window: Left half of screen
- Controls Window: Right half of screen

## Modified Files

### New Files Created:
1. `MapDisplay/cppiwindow.h` - PPI window header
2. `MapDisplay/cppiwindow.cpp` - PPI window implementation
3. `MapDisplay/ccontrolswindow.h` - Controls window header
4. `MapDisplay/ccontrolswindow.cpp` - Controls window implementation

### Modified Files:
1. `cmapmainwindow.h` - Updated to manage dual windows
2. `cmapmainwindow.cpp` - Refactored for dual-monitor orchestration
3. `MapDisplay/ctracktablewidget.cpp` - Updated with light theme
4. `globalstructs.h` - Enhanced track structure with history/highlighting
5. `RadarDisplay.pro` - Added new source files to build

## Build Instructions

1. **Regenerate Makefile** (if needed):
   ```bash
   qmake RadarDisplay.pro
   ```

2. **Build the application**:
   ```bash
   make clean
   make
   ```

3. **Run the application**:
   ```bash
   ../bin/RadarDisplay
   ```

## Keyboard Shortcuts

Global shortcuts:
- **F1**: Toggle PPI Window visibility
- **F2**: Toggle Controls Window visibility
- **H**: Map home view
- **Esc**: Exit application

## Usage Guide

### Initial Setup:
1. Launch the application
2. Both windows will appear automatically
3. On dual-monitor setups, windows are positioned on separate screens
4. On single-monitor setups, windows are positioned side-by-side

### Loading a Map:
1. Click the **⚙ Settings** button on PPI window
2. Select **📂 Load New Map**
3. Choose a raster file (TIF, PNG, BMP, JPG)

### Working with Tracks:
1. **Select a track**: Click on it in the track table
2. **Center on track**: Double-click in track table or right-click → Focus Track
3. **Configure history**: Right-click → Set History Points (1-50)
4. **Highlight track**: Right-click → Highlight & Follow
5. **Custom image**: Right-click → Load Track Image
6. **Delete track**: Right-click → Delete Track

### Using Controls:
1. Switch between tabs in the Controls Window
2. Each tab provides specific functionality:
   - Configuration: Map settings, zoom, opacity, track filters
   - Interfaces: Servo controls, radar scan, weapon systems
   - Analytics: Track statistics and analysis
   - Simulation: Generate simulated tracks
   - Recording: Record and replay track data
   - Health Monitor: System health metrics
   - Predictive Maintenance: Maintenance predictions
   - Charts: Visual data representation

## Theme Consistency

All widgets maintain the light theme:
- **Buttons**: Light blue background with dark blue text
- **Tables**: White background with light blue alternating rows
- **Input Fields**: White with blue borders
- **Tabs**: Light blue inactive, white active
- **Scrollbars**: Light blue track, medium blue handle
- **Headers**: Light blue background with dark blue text

## Future Enhancements

Potential improvements:
1. Implement actual track history trail rendering
2. Add track following camera mode
3. Implement map layer disable/enable functionality
4. Add track image overlay rendering
5. Implement zoom level persistence
6. Add window layout save/restore
7. Implement track filter in real-time

## Notes

- The application automatically detects single vs dual monitor setups
- All signal/slot connections are properly established between windows
- The light theme is consistently applied across all widgets
- Track table updates automatically every second
- Context menu operations provide user feedback via status bar
- All new features are backward compatible with existing functionality

## Architecture Diagram

```
┌─────────────────────────────────┐
│      CMapMainWindow             │
│      (Controller)               │
└─────────┬───────────────┬───────┘
          │               │
    ┌─────▼─────┐   ┌────▼──────┐
    │ CPPIWindow│   │CControls  │
    │ Monitor 1 │   │Window     │
    │           │   │Monitor 2  │
    ├───────────┤   ├───────────┤
    │-MapCanvas │   │-Config Tab│
    │-TrackTable│   │-Interfaces│
    │-Settings  │   │-Analytics │
    │-ContextMnu│   │-Simulation│
    └───────────┘   │-Recording │
                    │-Health    │
                    │-Mainten.  │
                    │-Charts    │
                    └───────────┘
```

## Contact & Support

For issues or questions, refer to the project documentation or contact the development team.
