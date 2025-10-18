# Track History Points Implementation

## Overview
This implementation adds configurable history points for tracks in the radar display system. Users can enable/disable history tracking for individual tracks and configure the maximum number of history points to maintain.

## Features

### 1. Configurable History Points
- **Default Limit**: 50 history points per track
- **Configurable Range**: 1-1000 points
- **Per-Track Control**: Each track can have history enabled/disabled independently

### 2. Context Menu Integration
- **Toggle History**: Right-click on any track to enable/disable history
- **Dynamic Menu**: Menu text updates to show current state and point count
- **Configure Settings**: Access to global history configuration

### 3. Visual History Display
- **Trail Visualization**: Smooth lines connecting historical positions
- **Fading Effect**: Older points are more transparent than newer ones
- **Color Coding**: History trails match track identity colors (green/red/yellow)
- **Point Markers**: Small dots at each historical position

## Usage

### Enabling History for a Track
1. Right-click on any track on the map
2. Select "📍 Show History (Max X points)" from context menu
3. History tracking begins immediately for that track

### Disabling History for a Track
1. Right-click on a track with history enabled
2. Select "📍 Hide History (X/Y points)" from context menu
3. History is cleared and tracking stops

### Configuring History Settings
1. Right-click on any track
2. Select "⚙️ Configure History" from context menu
3. Enter new maximum points value (1-1000)
4. Changes apply to all tracks immediately

## Technical Implementation

### Data Structures
```cpp
struct stTrackHistoryPoint {
    double lat;                 // Latitude at this point
    double lon;                 // Longitude at this point
    double alt;                 // Altitude at this point
    double heading;             // Heading at this point
    long long timestamp;        // Timestamp of this point
};

struct stTrackHistoryConfig {
    int maxHistoryPoints;       // Maximum number of history points (default 50)
    bool showHistory;           // Whether to show history trails
    int historyLineWidth;       // Width of history trail lines
    double historyAlpha;        // Alpha transparency for history trails
};
```

### Key Components

#### CDataWarehouse
- **History Storage**: `QHash<int, QList<stTrackHistoryPoint>> _m_trackHistory`
- **Enabled Tracks**: `QSet<int> _m_tracksWithHistoryEnabled`
- **Configuration**: `stTrackHistoryConfig _m_historyConfig`

#### CTrackLayer
- **History Rendering**: `drawTrackHistory()` method
- **Context Menu**: Dynamic menu updates based on track state
- **Configuration Dialog**: Input dialog for settings

### API Methods

#### CDataWarehouse
```cpp
// Get history points for a track
QList<stTrackHistoryPoint> getTrackHistory(int trackId);

// Toggle history for a track (returns new state)
bool toggleTrackHistory(int trackId);

// Check if history is enabled for a track
bool isTrackHistoryEnabled(int trackId);

// Get current configuration
stTrackHistoryConfig getHistoryConfig();

// Set maximum history points
void setMaxHistoryPoints(int maxPoints);
```

## Performance Considerations

### Memory Management
- History points are automatically limited to configured maximum
- Old points are removed when limit is exceeded (FIFO)
- History is cleared when track history is disabled

### Rendering Optimization
- History only drawn for tracks with history enabled
- Fading effect calculated efficiently using point age
- Minimal performance impact on track rendering

### Thread Safety
- All history operations are thread-safe
- Uses existing data warehouse mutex protection

## Configuration Persistence
Currently, history settings are runtime-only. For persistent configuration, consider:
- Adding settings to application configuration file
- Saving per-track history preferences
- Remembering global history settings between sessions

## Future Enhancements
- **Export History**: Save track history to file
- **History Playback**: Replay track movement over time
- **Advanced Filtering**: Filter history by time range or other criteria
- **Performance Metrics**: Track distance traveled, speed changes, etc.
- **History Styles**: Customizable line styles and colors