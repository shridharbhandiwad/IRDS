```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                             │
│  ███████╗ ██████╗ ██████╗ ██████╗ ██╗     ███████╗██████╗                 │
│  ╚══███╔╝██╔═══██╗██╔══██╗██╔══██╗██║     ██╔════╝██╔══██╗                │
│    ███╔╝ ██║   ██║██████╔╝██████╔╝██║     █████╗  ██████╔╝                │
│   ███╔╝  ██║   ██║██╔═══╝ ██╔═══╝ ██║     ██╔══╝  ██╔══██╗                │
│  ███████╗╚██████╔╝██║     ██║     ███████╗███████╗██║  ██║                │
│  ╚══════╝ ╚═════╝ ╚═╝     ╚═╝     ╚══════╝╚══════╝╚═╝  ╚═╝                │
│                                                                             │
│                     Z O P P L E R   S Y S T E M S                          │
│                   Advanced Radar Display Solutions                         │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

# **SOFTWARE DESIGN DOCUMENT**
## Integrated Radar Display System (IRDS)

---

**Document Information**

| Field | Value |
|-------|-------|
| **Document Title** | Software Design Document |
| **Product Name** | Integrated Radar Display System (IRDS) |
| **Version** | 1.0.0 |
| **Date** | October 13, 2025 |
| **Status** | Approved |
| **Classification** | Confidential |
| **Organization** | Zoppler Systems |
| **Prepared By** | Software Architecture Team |
| **Approved By** | Chief Technology Officer |

---

## DOCUMENT CONTROL

### Revision History

| Version | Date | Author | Description |
|---------|------|--------|-------------|
| 1.0.0 | 2025-10-13 | Architecture Team | Initial release version |
| 0.9.0 | 2025-10-01 | Architecture Team | Draft for review |

---

## TABLE OF CONTENTS

1. [Introduction](#1-introduction)
2. [System Architecture](#2-system-architecture)
3. [Component Design](#3-component-design)
4. [Data Design](#4-data-design)
5. [User Interface Design](#5-user-interface-design)
6. [Detailed Design](#6-detailed-design)
7. [Appendices](#7-appendices)

---

## 1. INTRODUCTION

### 1.1 Purpose

This Software Design Document (SDD) describes the software architecture and detailed design of the Integrated Radar Display System (IRDS). It provides:

- High-level system architecture
- Component design specifications
- Data structures and database design
- Interface specifications
- Design patterns and principles employed

### 1.2 Scope

This document covers the complete software design for IRDS version 1.0, including all modules, components, and their interactions.

### 1.3 Design Goals

| Goal | Description |
|------|-------------|
| **Modularity** | Loosely coupled components for maintainability |
| **Scalability** | Support for increasing track counts and features |
| **Performance** | Real-time response for radar data processing |
| **Reliability** | Robust error handling and recovery |
| **Usability** | Intuitive interface following HCI principles |
| **Maintainability** | Clear code structure and comprehensive documentation |

---

## 2. SYSTEM ARCHITECTURE

### 2.1 Architectural Overview

IRDS follows a layered architecture pattern with clear separation of concerns:

```
┌─────────────────────────────────────────────────────────────────┐
│                    PRESENTATION LAYER                           │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │  Main Window  │  Widgets  │  Dialogs  │  Visualization  │  │
│  └──────────────────────────────────────────────────────────┘  │
└────────────────────────┬────────────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────────────┐
│                   APPLICATION LAYER                             │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │  Track Manager  │  Simulation  │  Recording  │  Analytics │  │
│  │  Health Monitor │  Maintenance │  Config Manager         │  │
│  └──────────────────────────────────────────────────────────┘  │
└────────────────────────┬────────────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────────────┐
│                   DATA LAYER                                    │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │  Data Warehouse  │  Track Database  │  File I/O          │  │
│  │  Network Manager │  Coordinate Converter                 │  │
│  └──────────────────────────────────────────────────────────┘  │
└────────────────────────┬────────────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────────────┐
│                   INFRASTRUCTURE LAYER                          │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │  Qt Framework  │  QGIS Libraries  │  System Services    │  │
│  └──────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
```

### 2.2 Component Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                      CMapMainWindow                             │
│  ┌────────────────────────────────────────────────────────┐    │
│  │  - setupAnalyticsWidget()                              │    │
│  │  - setupSimulationWidget()                             │    │
│  │  - setupRecordingWidget()                              │    │
│  │  - setupHealthMonitorWidget()                          │    │
│  │  - setupPredictiveMaintenanceWidget()                  │    │
│  └────────────────────────────────────────────────────────┘    │
└─────┬───────────────────────────────────────────────────────────┘
      │
      ├──► CDataWarehouse (Central data repository)
      │    ├──► Track storage and management
      │    └──► Track injection from simulation/replay
      │
      ├──► CMapCanvas (QGIS-based map display)
      │    ├──► CTrackLayer (Track visualization)
      │    ├──► CPPILayer (PPI display)
      │    └──► CSearchBeamLayer (Beam pattern)
      │
      ├──► CSimulationWidget (Track simulation)
      │    └──► CUdpReceiver (UDP transmission)
      │
      ├──► CRecordingWidget (Recording & replay)
      │    ├──► Binary file I/O
      │    └──► Playback control
      │
      ├──► CHealthMonitorWidget (System health)
      │    ├──► Hardware monitoring
      │    └──► Software monitoring
      │
      ├──► CPredictiveMaintenanceWidget (Maintenance)
      │    ├──► Component tracking
      │    └──► Maintenance scheduling
      │
      ├──► CAnalyticsWidget (Analytics)
      ├──► CChartsWidget (Charts)
      ├──► CTrackTableWidget (Track table)
      ├──► CConfigPanelWidget (Configuration)
      └──► CInterfacesPanelWidget (Interfaces)
```

### 2.3 Design Patterns

| Pattern | Usage | Component |
|---------|-------|-----------|
| **Singleton** | Single instance of data warehouse | CDataWarehouse |
| **Observer** | Track update notifications | CTrackLayer, CTrackTableWidget |
| **Model-View** | Separation of data and presentation | All widgets |
| **Factory** | Layer creation | QGIS layers |
| **Strategy** | Different playback speeds | CRecordingWidget |
| **State** | Simulation states (Running, Paused, Stopped) | CSimulationWidget |

---

## 3. COMPONENT DESIGN

### 3.1 Core Components

#### 3.1.1 CMapMainWindow

**Purpose:** Main application window and widget container

**Responsibilities:**
- Initialize all child widgets
- Manage dock widget layout
- Handle keyboard shortcuts
- Coordinate inter-widget communication

**Key Attributes:**
```cpp
class CMapMainWindow : public QMainWindow {
private:
    CMapCanvas* m_mapCanvas;
    CDataWarehouse* m_dataWarehouse;
    CTrackTableWidget* m_trackTable;
    CSimulationWidget* m_simulationWidget;
    CRecordingWidget* m_recordingWidget;
    CHealthMonitorWidget* m_healthMonitor;
    CPredictiveMaintenanceWidget* m_predictiveMaintenance;
    CAnalyticsWidget* m_analyticsWidget;
    CChartsWidget* m_chartsWidget;
    CConfigPanelWidget* m_configPanel;
    CInterfacesPanelWidget* m_interfacesPanel;
};
```

**Key Methods:**
- `setupAnalyticsWidget()` - Initialize analytics widget
- `setupSimulationWidget()` - Initialize simulation widget
- `setupRecordingWidget()` - Initialize recording widget
- `setupHealthMonitorWidget()` - Initialize health monitor
- `setupPredictiveMaintenanceWidget()` - Initialize predictive maintenance
- `createShortcuts()` - Configure keyboard shortcuts
- `updateTrackTable()` - Update track table with current data

#### 3.1.2 CDataWarehouse

**Purpose:** Central repository for track data

**Responsibilities:**
- Store and manage all active tracks
- Provide track query interface
- Notify observers of track updates
- Handle track lifecycle (creation, update, deletion)

**Key Attributes:**
```cpp
class CDataWarehouse {
private:
    QMap<int, Track> m_tracks;  // Track ID to Track mapping
    QMutex m_mutex;              // Thread safety
    QList<Observer*> m_observers; // Observer pattern
};
```

**Key Methods:**
- `addTrack(Track track)` - Add new track
- `updateTrack(int id, Track track)` - Update existing track
- `removeTrack(int id)` - Remove track
- `getTrack(int id)` - Retrieve track by ID
- `getAllTracks()` - Retrieve all tracks
- `clearTracks()` - Remove all tracks

#### 3.1.3 CMapCanvas

**Purpose:** Geographic map display using QGIS

**Responsibilities:**
- Render base map layers
- Display track overlays
- Handle user interactions (zoom, pan)
- Coordinate conversion

**Integration:**
- Inherits from `QgsMapCanvas`
- Uses QGIS layer system
- WGS84 coordinate reference system

#### 3.1.4 CSimulationWidget

**Purpose:** Generate simulated radar tracks

**Responsibilities:**
- Generate tracks with configurable parameters
- Simulate track movement
- Transmit tracks via UDP
- Display simulation statistics

**State Machine:**
```
┌─────────┐  Start   ┌─────────┐  Pause   ┌─────────┐
│ Stopped │─────────►│ Running │─────────►│ Paused  │
└─────────┘          └─────────┘          └─────────┘
     ▲                    │                     │
     │ Stop               │ Stop                │ Resume
     │                    ▼                     ▼
     └────────────────────┴─────────────────────┘
```

**Key Attributes:**
```cpp
class CSimulationWidget : public QWidget {
private:
    QTimer* m_updateTimer;
    QList<SimulatedTrack> m_simulatedTracks;
    QUdpSocket* m_udpSocket;
    SimulationState m_state;
    SimulationConfig m_config;
};
```

#### 3.1.5 CRecordingWidget

**Purpose:** Record and replay radar sessions

**Responsibilities:**
- Record track data to binary files
- Manage recording library
- Replay recorded sessions with speed control
- Export and delete recordings

**File Format:**
- Binary format using Qt DataStream
- Versioned header for compatibility
- Frame-based structure with timestamps

**Key Attributes:**
```cpp
class CRecordingWidget : public QWidget {
private:
    QFile* m_recordingFile;
    QDataStream* m_dataStream;
    QTimer* m_replayTimer;
    RecordingState m_state;
    float m_playbackSpeed;
};
```

#### 3.1.6 CHealthMonitorWidget

**Purpose:** Monitor system health status

**Responsibilities:**
- Monitor hardware component status
- Monitor software module status
- Track system performance metrics
- Generate health reports
- Display alerts

**Key Attributes:**
```cpp
class CHealthMonitorWidget : public QWidget {
private:
    QMap<QString, ComponentHealth> m_hardwareModules;
    QMap<QString, ComponentHealth> m_softwareModules;
    SystemPerformance m_performance;
    QList<Alert> m_alerts;
    QTimer* m_refreshTimer;
};
```

**Health Calculation:**
```cpp
int calculateSystemHealth() {
    int totalHealth = 0;
    int moduleCount = 0;
    
    // Average hardware module health
    for (auto& module : m_hardwareModules) {
        totalHealth += module.healthPercentage;
        moduleCount++;
    }
    
    // Average software module health
    for (auto& module : m_softwareModules) {
        totalHealth += module.healthPercentage;
        moduleCount++;
    }
    
    return moduleCount > 0 ? totalHealth / moduleCount : 100;
}
```

#### 3.1.7 CPredictiveMaintenanceWidget

**Purpose:** Predict and schedule maintenance

**Responsibilities:**
- Track component lifetime and condition
- Calculate maintenance due dates
- Generate maintenance schedule
- Provide maintenance recommendations
- Track maintenance history

**Key Attributes:**
```cpp
class CPredictiveMaintenanceWidget : public QWidget {
private:
    QList<Component> m_components;
    QList<MaintenanceSchedule> m_schedule;
    QList<Recommendation> m_recommendations;
    QTimer* m_refreshTimer;
};
```

**Maintenance Prediction Algorithm:**
```cpp
int calculateDaysUntilMaintenance(Component& comp) {
    // Based on condition percentage and operating hours
    int baseMaintenanceInterval = comp.maxOperatingHours;
    int currentHours = comp.operatingHours;
    int remainingHours = baseMaintenanceInterval - currentHours;
    
    // Adjust for condition degradation
    float conditionFactor = comp.conditionPercentage / 100.0f;
    int adjustedHours = remainingHours * conditionFactor;
    
    // Convert to days (assuming 24hr operation)
    return adjustedHours / 24;
}
```

### 3.2 Supporting Components

#### 3.2.1 CTrackLayer

**Purpose:** QGIS layer for track visualization

**Responsibilities:**
- Render track symbols on map
- Apply color coding by identity
- Display track attributes
- Handle track selection

#### 3.2.2 CPPILayer

**Purpose:** Plan Position Indicator overlay

**Responsibilities:**
- Render PPI sweep pattern
- Animate rotation
- Display range rings

#### 3.2.3 CSearchBeamLayer

**Purpose:** Search beam pattern visualization

**Responsibilities:**
- Render beam pattern
- Update beam position
- Display beam parameters

#### 3.2.4 CTrackTableWidget

**Purpose:** Tabular track display

**Responsibilities:**
- Display all tracks in table format
- Support sorting and filtering
- Synchronize with map selection
- Update at 1 Hz minimum

#### 3.2.5 CUdpReceiver

**Purpose:** UDP network communication

**Responsibilities:**
- Receive track data via UDP
- Parse network packets
- Inject tracks into data warehouse
- Handle network errors

---

## 4. DATA DESIGN

### 4.1 Data Structures

#### 4.1.1 Track Structure

```cpp
struct Track {
    int trackId;              // Unique identifier
    double latitude;          // WGS84 latitude (degrees)
    double longitude;         // WGS84 longitude (degrees)
    double altitude;          // Altitude (meters MSL)
    double heading;           // True heading (degrees, 0-360)
    double speed;             // Ground speed (m/s)
    TrackIdentity identity;   // Friend, Hostile, Unknown
    uint64_t timestamp;       // Unix timestamp (milliseconds)
    QGeoCoordinate position;  // Qt geographic coordinate
};

enum TrackIdentity {
    FRIEND = 1,
    HOSTILE = 2,
    UNKNOWN = 3
};
```

#### 4.1.2 Recording Frame Structure

```cpp
struct RecordingFrame {
    uint64_t timestamp;       // Frame timestamp
    QList<Track> tracks;      // All tracks in this frame
};

struct RecordingHeader {
    QString magicNumber;      // "RADAR_RECORDING_V1"
    uint32_t version;         // Format version
    uint64_t startTimestamp;  // Recording start time
    uint32_t frameCount;      // Total frames
};
```

#### 4.1.3 Component Health Structure

```cpp
struct ComponentHealth {
    QString name;             // Component name
    QString icon;             // Icon identifier
    int healthPercentage;     // 0-100%
    HealthStatus status;      // Status enum
    QString statusText;       // Human-readable status
    QDateTime lastCheck;      // Last health check time
};

enum HealthStatus {
    EXCELLENT,      // 90-100%
    GOOD,          // 75-89%
    FAIR,          // 60-74%
    POOR,          // 40-59%
    SERVICE_REQUIRED, // 20-39%
    CRITICAL       // 0-19%
};
```

#### 4.1.4 Maintenance Component Structure

```cpp
struct Component {
    QString name;                // Component name
    QString category;            // RF, Mechanical, Power, etc.
    int conditionPercentage;     // 0-100%
    int daysUntilMaintenance;   // Days until next service
    int operatingHours;         // Total operating hours
    QDate lastMaintenance;      // Last service date
    MaintenanceStatus status;   // Status enum
};

enum MaintenanceStatus {
    EXCELLENT,      // 90+ days
    GOOD,          // 60-90 days
    FAIR,          // 30-60 days
    POOR,          // 7-30 days
    SERVICE_REQUIRED, // 1-7 days
    CRITICAL       // 0 days
};
```

### 4.2 Data Flow Diagrams

#### 4.2.1 Track Data Flow

```
┌──────────────┐
│ Radar System │
└──────┬───────┘
       │ UDP
       ▼
┌──────────────┐
│ CUdpReceiver │
└──────┬───────┘
       │ addTrack()
       ▼
┌──────────────┐      ┌─────────────────┐
│CDataWarehouse├─────►│ CTrackLayer     │
└──────┬───────┘      └─────────────────┘
       │
       ├─────────────►┌─────────────────┐
       │              │CTrackTableWidget│
       │              └─────────────────┘
       │
       └─────────────►┌─────────────────┐
                      │ CAnalyticsWidget│
                      └─────────────────┘
```

#### 4.2.2 Recording Data Flow

```
┌──────────────┐
│CDataWarehouse│
└──────┬───────┘
       │ Track updates
       ▼
┌──────────────────┐
│CRecordingWidget  │
│  (Recording)     │
└──────┬───────────┘
       │ Write to disk
       ▼
┌──────────────────┐
│ Binary File      │
│ (.rdr format)    │
└──────┬───────────┘
       │ Read from disk
       ▼
┌──────────────────┐
│CRecordingWidget  │
│  (Replay)        │
└──────┬───────────┘
       │ Inject tracks
       ▼
┌──────────────────┐
│CDataWarehouse    │
└──────────────────┘
```

### 4.3 Database Schema

IRDS uses file-based storage rather than a traditional database:

| Storage Type | Purpose | Format |
|--------------|---------|--------|
| **Recordings** | Session data | Binary (.rdr) |
| **Configuration** | User settings | XML/INI |
| **Logs** | System logs | Text |
| **Reports** | Exported reports | TXT |

---

## 5. USER INTERFACE DESIGN

### 5.1 UI Architecture

IRDS uses Qt Widgets with a dock widget-based layout:

```
┌─────────────────────────────────────────────────────────────┐
│                    Main Window Title Bar                    │
├────────────┬────────────────────────────┬────────────────────┤
│            │                            │                    │
│   Left     │     Central Widget         │      Right         │
│   Dock     │     (Map Canvas)           │      Dock          │
│   Area     │                            │      Area          │
│            │                            │                    │
│  Config    │                            │   Track Table      │
│  ┌──────┐  │                            │   ┌─────────────┐  │
│  │      │  │                            │   │             │  │
│  └──────┘  │                            │   └─────────────┘  │
│  Interfaces│                            │   Analytics        │
│  ┌──────┐  │                            │   ┌─────────────┐  │
│  │ [TAB]│  │                            │   │    [TAB]    │  │
│  └──────┘  │                            │   └─────────────┘  │
│            │                            │                    │
│  Simulation│                            │   Health Monitor   │
│  ┌──────┐  │                            │   ┌─────────────┐  │
│  │      │  │                            │   │             │  │
│  └──────┘  │                            │   └─────────────┘  │
│  Recording │                            │   Predictive       │
│  ┌──────┐  │                            │   ┌─────────────┐  │
│  │ [TAB]│  │                            │   │    [TAB]    │  │
│  └──────┘  │                            │   └─────────────┘  │
│            │                            │                    │
├────────────┴────────────────────────────┴────────────────────┤
│                    Bottom Dock Area                          │
│                    (Charts - Hidden)                         │
├──────────────────────────────────────────────────────────────┤
│                    Status Bar                                │
└──────────────────────────────────────────────────────────────┘
```

### 5.2 Theme Design

#### 5.2.1 Color Palette

**Base Colors:**
- Background Dark: `#0f172a`
- Background Medium: `#1e293b`
- Background Light: `#1a202c`
- Border: `#4a5568`
- Border Light: `#334155`
- Text Primary: `#ffffff`
- Text Secondary: `#e2e8f0`
- Text Muted: `#94a3b8`

**Status Colors:**
- Success/Healthy: `#4ade80` (Green)
- Warning: `#fbbf24` (Yellow)
- Error/Critical: `#ef4444` (Red)
- Info: `#60a5fa` (Blue)

**Widget Accent Colors:**
- Simulation: Purple gradient `#667eea` to `#764ba2`
- Recording: Red gradient `#dc2626` to `#7c2d12`
- Health: Green gradient `#10b981` to `#059669`
- Predictive: Purple gradient `#8b5cf6` to `#6d28d9`
- Config: Blue gradient `#667eea` to `#764ba2`

#### 5.2.2 Typography

- **Headers:** Bold, 16-18pt
- **Body Text:** Regular, 12-14pt
- **Labels:** Regular, 11-12pt
- **Status Text:** Monospace, 11pt
- **Font Family:** System default sans-serif

#### 5.2.3 UI Elements

**Buttons:**
```css
QPushButton {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                               stop:0 #667eea, stop:1 #764ba2);
    border: none;
    border-radius: 6px;
    color: white;
    padding: 8px 16px;
}
QPushButton:hover {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                               stop:0 #5568d3, stop:1 #6b4193);
}
```

**Progress Bars:**
```css
QProgressBar {
    background-color: #1e293b;
    border: 1px solid #4a5568;
    border-radius: 4px;
    text-align: center;
}
QProgressBar::chunk {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                               stop:0 #4ade80, stop:1 #10b981);
    border-radius: 3px;
}
```

### 5.3 Widget Specifications

#### 5.3.1 Simulation Widget

**Layout:**
- Top: Control buttons (Start, Pause, Stop, Reset)
- Middle: Configuration panel (sliders, spin boxes, combo boxes)
- Bottom: Statistics panel and track table

**Controls:**
- Number of Tracks: Spin box (1-50)
- Max Range: Spin box (1000-50000 meters)
- Update Rate: Spin box (100-5000 ms)
- Azimuth Spread: Spin box (30-360 degrees)
- Speed Min/Max: Dual spin boxes (m/s)
- Identity: Combo box (Friend/Hostile/Unknown/Random)
- Random Movement: Checkbox

#### 5.3.2 Recording Widget

**Layout:**
- Top: Recording controls
- Middle: Replay controls
- Bottom: Recording library browser

**Recording Controls:**
- Record button (red dot icon)
- Pause button
- Stop button
- Duration display
- Frame count display

**Replay Controls:**
- File selector
- Play button
- Pause button
- Stop button
- Speed selector (dropdown)
- Progress bar
- Frame counter

---

## 6. DETAILED DESIGN

### 6.1 Algorithm Specifications

#### 6.1.1 Track Simulation Algorithm

```cpp
void CSimulationWidget::generateTracks() {
    m_simulatedTracks.clear();
    
    // Calculate azimuth step
    double azimuthStep = m_config.azimuthSpread / m_config.trackCount;
    double startAzimuth = (360.0 - m_config.azimuthSpread) / 2.0;
    
    for (int i = 0; i < m_config.trackCount; i++) {
        SimulatedTrack track;
        
        // Generate track ID
        track.id = i + 1;
        
        // Calculate azimuth
        double azimuth = startAzimuth + (i * azimuthStep);
        if (m_config.randomizeAzimuth) {
            azimuth += QRandomGenerator::global()->bounded(-10.0, 10.0);
        }
        
        // Calculate range
        double range = QRandomGenerator::global()->bounded(
            m_config.maxRange * 0.3, m_config.maxRange);
        
        // Convert polar to Cartesian (relative to radar)
        double x = range * sin(qDegreesToRadians(azimuth));
        double y = range * cos(qDegreesToRadians(azimuth));
        
        // Convert to geographic coordinates
        track.position = convertToGeoCoordinate(x, y);
        
        // Random speed within range
        track.speed = QRandomGenerator::global()->bounded(
            m_config.speedMin, m_config.speedMax);
        
        // Random heading
        track.heading = QRandomGenerator::global()->bounded(0.0, 360.0);
        
        // Assign identity
        track.identity = assignIdentity(m_config.identityMode);
        
        m_simulatedTracks.append(track);
    }
}

void CSimulationWidget::updateTracks() {
    for (auto& track : m_simulatedTracks) {
        if (m_config.randomMovement) {
            // Random heading change (±5 degrees)
            track.heading += QRandomGenerator::global()->bounded(-5.0, 5.0);
            if (track.heading < 0) track.heading += 360;
            if (track.heading >= 360) track.heading -= 360;
            
            // Random speed variation (±10%)
            double speedVariation = track.speed * 0.1;
            track.speed += QRandomGenerator::global()->bounded(
                -speedVariation, speedVariation);
        }
        
        // Calculate distance traveled (speed * time)
        double distance = track.speed * (m_config.updateRate / 1000.0);
        
        // Update position
        track.position = calculateNewPosition(
            track.position, track.heading, distance);
    }
    
    // Transmit via UDP
    transmitTracks(m_simulatedTracks);
}
```

#### 6.1.2 Recording Algorithm

```cpp
void CRecordingWidget::recordFrame() {
    // Get all current tracks from data warehouse
    QList<Track> tracks = m_dataWarehouse->getAllTracks();
    
    // Create frame
    RecordingFrame frame;
    frame.timestamp = QDateTime::currentMSecsSinceEpoch();
    frame.tracks = tracks;
    
    // Write to file
    *m_dataStream << frame.timestamp;
    *m_dataStream << (quint32)frame.tracks.size();
    
    for (const Track& track : frame.tracks) {
        *m_dataStream << track.trackId;
        *m_dataStream << track.latitude;
        *m_dataStream << track.longitude;
        *m_dataStream << track.altitude;
        *m_dataStream << track.heading;
        *m_dataStream << track.speed;
        *m_dataStream << (qint32)track.identity;
        *m_dataStream << track.timestamp;
    }
    
    m_frameCount++;
    updateUI();
}

void CRecordingWidget::replayFrame() {
    if (m_dataStream->atEnd()) {
        stopReplay();
        return;
    }
    
    // Read frame
    quint64 timestamp;
    quint32 trackCount;
    *m_dataStream >> timestamp >> trackCount;
    
    QList<Track> tracks;
    for (quint32 i = 0; i < trackCount; i++) {
        Track track;
        qint32 identity;
        
        *m_dataStream >> track.trackId;
        *m_dataStream >> track.latitude;
        *m_dataStream >> track.longitude;
        *m_dataStream >> track.altitude;
        *m_dataStream >> track.heading;
        *m_dataStream >> track.speed;
        *m_dataStream >> identity;
        *m_dataStream >> track.timestamp;
        
        track.identity = (TrackIdentity)identity;
        tracks.append(track);
    }
    
    // Inject tracks into data warehouse
    m_dataWarehouse->clearTracks();
    for (const Track& track : tracks) {
        m_dataWarehouse->addTrack(track);
    }
    
    m_currentFrame++;
    updateUI();
}
```

### 6.2 Error Handling

#### 6.2.1 Error Categories

| Category | Example | Handling Strategy |
|----------|---------|-------------------|
| **Network Errors** | UDP socket failure | Log error, retry connection, notify user |
| **File I/O Errors** | Recording write failure | Stop recording, save partial file, notify user |
| **Memory Errors** | Allocation failure | Reduce track count, free resources, notify user |
| **Data Validation** | Invalid coordinates | Discard track, log warning, continue operation |
| **User Input** | Invalid configuration | Show error message, revert to default |

#### 6.2.2 Error Handling Pattern

```cpp
bool CRecordingWidget::startRecording() {
    try {
        // Ensure directory exists
        QDir dir(QDir::homePath() + "/RadarRecordings");
        if (!dir.exists() && !dir.mkpath(".")) {
            throw std::runtime_error("Failed to create recording directory");
        }
        
        // Create file
        QString filename = QString("recording_%1.rdr")
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));
        m_recordingFile = new QFile(dir.filePath(filename));
        
        if (!m_recordingFile->open(QIODevice::WriteOnly)) {
            throw std::runtime_error("Failed to open recording file");
        }
        
        // Write header
        m_dataStream = new QDataStream(m_recordingFile);
        writeHeader();
        
        // Start recording timer
        m_recordingTimer->start(1000); // 1 Hz
        m_state = RECORDING;
        
        return true;
        
    } catch (const std::exception& e) {
        qCritical() << "Recording error:" << e.what();
        QMessageBox::critical(this, "Recording Error", 
            QString("Failed to start recording: %1").arg(e.what()));
        cleanup();
        return false;
    }
}
```

---

## 7. APPENDICES

### 7.1 Appendix A: Class Hierarchy

```
QObject
├── CDataWarehouse
├── CUdpReceiver
└── QWidget
    ├── QMainWindow
    │   └── CMapMainWindow
    └── Custom Widgets
        ├── CSimulationWidget
        ├── CRecordingWidget
        ├── CHealthMonitorWidget
        ├── CPredictiveMaintenanceWidget
        ├── CAnalyticsWidget
        ├── CChartsWidget
        ├── CTrackTableWidget
        ├── CConfigPanelWidget
        └── CInterfacesPanelWidget

QgsMapCanvas
└── CMapCanvas

QgsPluginLayer
├── CTrackLayer
├── CPPILayer
└── CSearchBeamLayer
```

### 7.2 Appendix B: Build System

**Project File Structure:**
```
RadarDisplay.pro (Main project file)
├── SOURCES (*.cpp files)
├── HEADERS (*.h files)
├── FORMS (*.ui files)
├── RESOURCES (*.qrc files)
└── LIBS (External libraries)
```

**Dependencies:**
- Qt 5.x (core, gui, widgets, xml, network, concurrent, qml, quick, charts)
- QGIS libraries (qgis_core, qgis_gui, qgis_analysis)
- GEOS (Geometry Engine Open Source)
- PROJ (Cartographic Projections Library)
- SpatialIndex

### 7.3 Appendix C: Thread Safety

**Thread-Safe Components:**
- CDataWarehouse (mutex-protected)
- CUdpReceiver (separate thread)
- File I/O operations (queued)

**Thread Safety Pattern:**
```cpp
void CDataWarehouse::addTrack(const Track& track) {
    QMutexLocker locker(&m_mutex);
    m_tracks[track.trackId] = track;
    emit trackAdded(track.trackId);
}
```

---

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                             │
│                          ZOPPLER SYSTEMS                                    │
│                      Integrated Radar Display System                        │
│                                                                             │
│  Document: Software Design Document                                         │
│  Version: 1.0.0                                                            │
│  Date: October 13, 2025                                                    │
│  Classification: Confidential                                               │
│                                                                             │
│  © 2025 Zoppler Systems. All rights reserved.                             │
│  This document contains proprietary and confidential information.           │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

**END OF DOCUMENT**
