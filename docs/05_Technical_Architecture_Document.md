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

# **TECHNICAL ARCHITECTURE DOCUMENT**
## Integrated Radar Display System (IRDS)

---

**Document Information**

| Field | Value |
|-------|-------|
| **Document Title** | Technical Architecture Document |
| **Product Name** | Integrated Radar Display System (IRDS) |
| **Version** | 1.0.0 |
| **Date** | October 13, 2025 |
| **Status** | Approved |
| **Classification** | Confidential |
| **Organization** | Zoppler Systems |
| **Prepared By** | Architecture Team |

---

## TABLE OF CONTENTS

1. [Executive Summary](#1-executive-summary)
2. [Architectural Goals and Constraints](#2-architectural-goals-and-constraints)
3. [System Context](#3-system-context)
4. [Architectural Patterns](#4-architectural-patterns)
5. [Component Architecture](#5-component-architecture)
6. [Data Architecture](#6-data-architecture)
7. [Deployment Architecture](#7-deployment-architecture)
8. [Security Architecture](#8-security-architecture)
9. [Performance Architecture](#9-performance-architecture)

---

## 1. EXECUTIVE SUMMARY

### 1.1 Purpose

This Technical Architecture Document describes the technical architecture of the Integrated Radar Display System (IRDS), providing detailed information on system structure, components, data flows, and deployment strategies.

### 1.2 Architectural Overview

IRDS is built on a modular, layered architecture using Qt C++ framework for the presentation layer and QGIS libraries for geospatial visualization. The system follows Model-View-Controller (MVC) patterns with clear separation between data management, business logic, and presentation.

**Key Architectural Characteristics:**
- **Modularity:** Loosely coupled components
- **Scalability:** Support for increasing load
- **Maintainability:** Clear structure and documentation
- **Performance:** Real-time data processing
- **Reliability:** Robust error handling

---

## 2. ARCHITECTURAL GOALS AND CONSTRAINTS

### 2.1 Architectural Goals

| Goal | Description | Priority |
|------|-------------|----------|
| **Real-Time Performance** | Process and display tracks at >1 Hz update rate | High |
| **Modularity** | Independent, replaceable components | High |
| **Extensibility** | Easy addition of new features | Medium |
| **Maintainability** | Clear code structure, well-documented | High |
| **Reliability** | 99.9% uptime during operations | High |
| **Usability** | Intuitive user interface | Medium |

### 2.2 Technical Constraints

| Constraint | Impact |
|------------|--------|
| **Qt Framework** | GUI development limited to Qt capabilities |
| **C++ Language** | Memory management and performance considerations |
| **Linux Platform** | Platform-specific optimizations, no Windows support in v1.0 |
| **QGIS Dependency** | Tied to QGIS library versions and capabilities |
| **UDP Protocol** | Limited reliability, no guaranteed delivery |
| **Single Application** | Desktop application, not web-based |

### 2.3 Architectural Principles

1. **Separation of Concerns:** Each component has a single, well-defined responsibility
2. **DRY (Don't Repeat Yourself):** Reuse code through abstraction
3. **SOLID Principles:** Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, Dependency Inversion
4. **Loose Coupling:** Minimize dependencies between components
5. **High Cohesion:** Related functionality grouped together
6. **Fail Fast:** Detect and report errors early
7. **Thread Safety:** Proper synchronization for concurrent access

---

## 3. SYSTEM CONTEXT

### 3.1 System Context Diagram

```
┌────────────────────────────────────────────────────────────────┐
│                    EXTERNAL SYSTEMS                            │
│                                                                │
│  ┌──────────────┐         ┌──────────────┐                   │
│  │Radar Hardware│         │Network Time  │                   │
│  │  Systems     │         │  Protocol    │                   │
│  └──────┬───────┘         └──────┬───────┘                   │
│         │ UDP Tracks              │ Time Sync                 │
│         │                         │                           │
└─────────┼─────────────────────────┼───────────────────────────┘
          │                         │
          │                         │
┌─────────▼─────────────────────────▼───────────────────────────┐
│                                                                │
│        INTEGRATED RADAR DISPLAY SYSTEM (IRDS)                 │
│                                                                │
│  ┌──────────────────────────────────────────────────────┐    │
│  │            Presentation Layer                        │    │
│  │  (Qt Widgets, QGIS Map Canvas, UI Components)        │    │
│  └────────────────────┬─────────────────────────────────┘    │
│                       │                                       │
│  ┌────────────────────▼─────────────────────────────────┐    │
│  │            Application Layer                         │    │
│  │  (Business Logic, Track Management, Analytics)       │    │
│  └────────────────────┬─────────────────────────────────┘    │
│                       │                                       │
│  ┌────────────────────▼─────────────────────────────────┐    │
│  │            Data Layer                                │    │
│  │  (Data Warehouse, File I/O, Network I/O)             │    │
│  └────────────────────┬─────────────────────────────────┘    │
│                       │                                       │
│  ┌────────────────────▼─────────────────────────────────┐    │
│  │         Infrastructure Layer                         │    │
│  │  (Qt Framework, QGIS, OS Services)                   │    │
│  └──────────────────────────────────────────────────────┘    │
│                                                                │
└────────────────────────┬───────────────────────────────────────┘
                         │
                         │ File I/O
                         ▼
┌────────────────────────────────────────────────────────────────┐
│                    EXTERNAL STORAGE                            │
│                                                                │
│  ┌──────────────┐         ┌──────────────┐                   │
│  │  Recording   │         │Configuration │                   │
│  │    Files     │         │    Files     │                   │
│  └──────────────┘         └──────────────┘                   │
└────────────────────────────────────────────────────────────────┘
```

### 3.2 External Interfaces

| Interface | Type | Protocol | Purpose |
|-----------|------|----------|---------|
| **Radar Systems** | Network | UDP/IP | Receive track data |
| **File System** | Storage | POSIX | Recording storage |
| **Display** | Hardware | X11/Wayland | Graphics output |
| **Network** | Hardware | Ethernet | Data reception |
| **User Input** | Hardware | Keyboard/Mouse | User interaction |

---

## 4. ARCHITECTURAL PATTERNS

### 4.1 Layered Architecture

IRDS uses a 4-layer architecture:

```
┌─────────────────────────────────────────────────────┐
│          PRESENTATION LAYER                         │
│  • User Interface Components                        │
│  • Widgets and Dialogs                             │
│  • QGIS Map Canvas                                 │
│  • Visual Elements                                  │
└────────────────┬────────────────────────────────────┘
                 │ UI Events, Data Requests
                 ▼
┌─────────────────────────────────────────────────────┐
│          APPLICATION LAYER                          │
│  • Business Logic                                   │
│  • Track Management                                 │
│  • Simulation Engine                                │
│  • Recording/Replay Logic                           │
│  • Health Monitoring                                │
│  • Maintenance Prediction                           │
└────────────────┬────────────────────────────────────┘
                 │ Data Operations
                 ▼
┌─────────────────────────────────────────────────────┐
│          DATA LAYER                                 │
│  • Data Warehouse                                   │
│  • File I/O Operations                              │
│  • Network Communication                            │
│  • Coordinate Transformation                        │
└────────────────┬────────────────────────────────────┘
                 │ System Calls
                 ▼
┌─────────────────────────────────────────────────────┐
│          INFRASTRUCTURE LAYER                       │
│  • Qt Framework                                     │
│  • QGIS Libraries                                   │
│  • Operating System                                 │
│  • Hardware Drivers                                 │
└─────────────────────────────────────────────────────┘
```

### 4.2 Model-View-Controller (MVC)

```
┌──────────────┐        ┌──────────────┐        ┌──────────────┐
│    MODEL     │◄───────│  CONTROLLER  │◄───────│     VIEW     │
│              │        │              │        │              │
│ • Track Data │        │ • Event      │        │ • Map Canvas │
│ • Config     │        │   Handling   │        │ • Widgets    │
│ • State      │        │ • Business   │        │ • Tables     │
│              │        │   Logic      │        │              │
└──────┬───────┘        └──────────────┘        └──────────────┘
       │                                                 ▲
       │ Notify Changes                                  │
       └─────────────────────────────────────────────────┘
```

**Example: Track Display**
- **Model:** CDataWarehouse (stores track data)
- **View:** CTrackLayer, CTrackTableWidget (displays tracks)
- **Controller:** CMapMainWindow (handles user interactions)

### 4.3 Observer Pattern

Used for track updates:

```
┌─────────────────┐
│ CDataWarehouse  │  (Subject)
│   (Subject)     │
└────────┬────────┘
         │
         │ notifyObservers()
         │
         ├──────────────┬──────────────┬──────────────┐
         │              │              │              │
         ▼              ▼              ▼              ▼
┌───────────────┐ ┌────────────┐ ┌────────────┐ ┌────────────┐
│  CTrackLayer  │ │TrackTable  │ │ Analytics  │ │ Recording  │
│   (Observer)  │ │ (Observer) │ │ (Observer) │ │ (Observer) │
└───────────────┘ └────────────┘ └────────────┘ └────────────┘
```

### 4.4 Strategy Pattern

Used for playback speeds:

```
┌──────────────────────┐
│ PlaybackStrategy     │ (Interface)
└──────────────────────┘
           △
           │ implements
     ┌─────┴─────────┬──────────┬──────────┐
     │               │          │          │
┌────────────┐ ┌────────────┐ ┌────────────┐ ┌────────────┐
│ QuarterSpeed│ │ HalfSpeed │ │ NormalSpeed│ │DoubleSpeed│
└────────────┘ └────────────┘ └────────────┘ └────────────┘
```

### 4.5 Factory Pattern

Used for QGIS layer creation:

```
┌───────────────────┐
│   LayerFactory    │
└─────────┬─────────┘
          │
          │ createLayer(type)
          │
     ┌────┴────────┬──────────┬─────────────┐
     │             │          │             │
┌────────────┐ ┌────────────┐ ┌────────────┐
│ TrackLayer │ │  PPILayer  │ │ BeamLayer  │
└────────────┘ └────────────┘ └────────────┘
```

---

## 5. COMPONENT ARCHITECTURE

### 5.1 High-Level Component Diagram

```
┌────────────────────────────────────────────────────────────┐
│                    CMapMainWindow                          │
│                  (Main Application)                        │
└─────┬──────────────────────────────────────────────────────┘
      │
      ├──► CDataWarehouse (Central Data Repository)
      │    └──► QMap<int, Track>
      │
      ├──► CMapCanvas (QGIS Map Display)
      │    ├──► CTrackLayer
      │    ├──► CPPILayer
      │    └──► CSearchBeamLayer
      │
      ├──► CUdpReceiver (Network Input)
      │    └──► QUdpSocket
      │
      ├──► Widgets (User Interface)
      │    ├──► CSimulationWidget
      │    ├──► CRecordingWidget
      │    ├──► CHealthMonitorWidget
      │    ├──► CPredictiveMaintenanceWidget
      │    ├──► CTrackTableWidget
      │    ├──► CAnalyticsWidget
      │    ├──► CChartsWidget
      │    ├──► CConfigPanelWidget
      │    └──► CInterfacesPanelWidget
      │
      └──► Utility Components
           ├──► CoordinateConverter
           └──► Matrix
```

### 5.2 Core Components

#### 5.2.1 CMapMainWindow

**Responsibilities:**
- Application lifecycle management
- Widget container and coordinator
- Keyboard shortcut handling
- Menu and toolbar management

**Key Methods:**
```cpp
void setupAnalyticsWidget();
void setupSimulationWidget();
void setupRecordingWidget();
void setupHealthMonitorWidget();
void setupPredictiveMaintenanceWidget();
void createShortcuts();
void updateTrackTable();
```

**Dependencies:**
- All widget classes
- CDataWarehouse
- CMapCanvas

#### 5.2.2 CDataWarehouse

**Responsibilities:**
- Central track data storage
- Track lifecycle management
- Observer pattern implementation
- Thread-safe data access

**Key Methods:**
```cpp
void addTrack(const Track& track);
void updateTrack(int id, const Track& track);
void removeTrack(int id);
Track getTrack(int id) const;
QList<Track> getAllTracks() const;
void clearTracks();
void registerObserver(Observer* obs);
void notifyObservers();
```

**Thread Safety:**
```cpp
QMutex m_mutex;  // Protects m_tracks
QMutexLocker locker(&m_mutex);  // Used in all public methods
```

#### 5.2.3 CMapCanvas

**Responsibilities:**
- Geographic map rendering
- Layer management
- User interaction (zoom, pan)
- Coordinate system management

**Inheritance:**
```cpp
class CMapCanvas : public QgsMapCanvas
```

**Key Features:**
- WGS84 coordinate reference system
- OpenStreetMap base layer
- Custom symbol layers for tracks
- Real-time rendering updates

#### 5.2.4 CSimulationWidget

**Responsibilities:**
- Track simulation
- UDP transmission
- Simulation control (start/pause/stop)
- Statistics tracking

**State Machine:**
```
STOPPED ──start──> RUNNING ──pause──> PAUSED
   ▲                  │                  │
   │                  │                  │
   └──────stop────────┴───────resume─────┘
```

**Update Loop:**
```cpp
void updateTracks() {
    // Calculate new positions
    for (auto& track : m_simulatedTracks) {
        // Apply physics
        // Update position based on heading and speed
        // Handle boundary conditions
    }
    // Transmit via UDP
    transmitTracks(m_simulatedTracks);
}
```

### 5.3 Widget Components

#### Component Specifications

| Component | Purpose | Update Rate | Data Source |
|-----------|---------|-------------|-------------|
| **CTrackTableWidget** | Track list display | 1 Hz | CDataWarehouse |
| **CAnalyticsWidget** | Track analysis | 1 Hz | CDataWarehouse |
| **CChartsWidget** | Real-time charts | 1 Hz | CDataWarehouse |
| **CConfigPanelWidget** | Configuration UI | On-demand | Local config |
| **CInterfacesPanelWidget** | Hardware status | 1 Hz | System |
| **CSimulationWidget** | Track simulation | Configurable | Internal |
| **CRecordingWidget** | Recording/replay | 1 Hz (record) | CDataWarehouse |
| **CHealthMonitorWidget** | System health | 0.2 Hz (5s) | System |
| **CPredictiveMaintenanceWidget** | Maintenance | 0.1 Hz (10s) | System |

---

## 6. DATA ARCHITECTURE

### 6.1 Data Model

#### 6.1.1 Core Entities

```
┌─────────────────────────────────────────────┐
│              Track                          │
├─────────────────────────────────────────────┤
│ + trackId : int                             │
│ + latitude : double                         │
│ + longitude : double                        │
│ + altitude : double                         │
│ + heading : double                          │
│ + speed : double                            │
│ + identity : TrackIdentity                  │
│ + timestamp : uint64_t                      │
│ + position : QGeoCoordinate                 │
└─────────────────────────────────────────────┘

┌─────────────────────────────────────────────┐
│         SimulatedTrack                      │
├─────────────────────────────────────────────┤
│ + id : int                                  │
│ + position : QGeoCoordinate                 │
│ + heading : double                          │
│ + speed : double                            │
│ + identity : TrackIdentity                  │
│ + updateTime : uint64_t                     │
└─────────────────────────────────────────────┘

┌─────────────────────────────────────────────┐
│        ComponentHealth                      │
├─────────────────────────────────────────────┤
│ + name : QString                            │
│ + icon : QString                            │
│ + healthPercentage : int                    │
│ + status : HealthStatus                     │
│ + statusText : QString                      │
│ + lastCheck : QDateTime                     │
└─────────────────────────────────────────────┘

┌─────────────────────────────────────────────┐
│           Component                         │
├─────────────────────────────────────────────┤
│ + name : QString                            │
│ + category : QString                        │
│ + conditionPercentage : int                 │
│ + daysUntilMaintenance : int                │
│ + operatingHours : int                      │
│ + lastMaintenance : QDate                   │
│ + status : MaintenanceStatus                │
└─────────────────────────────────────────────┘
```

### 6.2 Data Storage

#### 6.2.1 In-Memory Storage

**Track Storage:**
```cpp
QMap<int, Track> m_tracks;  // Key: trackId, Value: Track data
```

**Advantages:**
- Fast access (O(log n))
- Automatic sorting by track ID
- Easy lookup, insertion, deletion

#### 6.2.2 File-Based Storage

**Recording File Structure:**
```
┌──────────────────────────────────────────┐
│           File Header                    │
├──────────────────────────────────────────┤
│ Magic Number: "RADAR_RECORDING_V1"       │
│ Version: uint32                          │
│ Start Timestamp: uint64                  │
│ Frame Count: uint32                      │
├──────────────────────────────────────────┤
│           Frame 1                        │
├──────────────────────────────────────────┤
│ Timestamp: uint64                        │
│ Track Count: uint32                      │
│ Track Data: [Track1, Track2, ...]       │
├──────────────────────────────────────────┤
│           Frame 2                        │
├──────────────────────────────────────────┤
│ ...                                      │
└──────────────────────────────────────────┘
```

**Binary Format:**
- Uses Qt QDataStream for serialization
- Platform-independent binary format
- Versioned for future compatibility

### 6.3 Data Flow

#### 6.3.1 Track Data Flow (Live)

```
Radar → UDP → CUdpReceiver → parse() → CDataWarehouse.addTrack()
                                              │
                            ┌─────────────────┼─────────────────┐
                            │                 │                 │
                            ▼                 ▼                 ▼
                      CTrackLayer    CTrackTableWidget   CRecordingWidget
                            │                 │                 │
                            ▼                 ▼                 ▼
                     Map Display      Table Display      File Write
```

#### 6.3.2 Simulation Data Flow

```
CSimulationWidget.generateTracks()
         │
         ▼
  Update positions based on physics
         │
         ▼
  Transmit via UDP (localhost:2025)
         │
         ▼
  CUdpReceiver → CDataWarehouse
         │
         ▼
  Display in UI
```

#### 6.3.3 Recording Data Flow

```
CDataWarehouse → CRecordingWidget.recordFrame()
                        │
                        ▼
                 Create RecordingFrame
                        │
                        ▼
              Serialize to QDataStream
                        │
                        ▼
                Write to QFile (~/ RadarRecordings/)
```

---

## 7. DEPLOYMENT ARCHITECTURE

### 7.1 Physical Deployment

```
┌─────────────────────────────────────────────────────────┐
│               Workstation/Server                        │
│  ┌───────────────────────────────────────────────────┐  │
│  │          Operating System (Linux)                 │  │
│  │                                                   │  │
│  │  ┌────────────────────────────────────────────┐  │  │
│  │  │         IRDS Application                   │  │  │
│  │  │   /opt/irds/bin/RadarDisplay               │  │  │
│  │  └────────────────┬───────────────────────────┘  │  │
│  │                   │                               │  │
│  │  ┌────────────────▼───────────────────────────┐  │  │
│  │  │     Qt Runtime Environment                 │  │  │
│  │  │     QGIS Libraries                         │  │  │
│  │  │     System Libraries                       │  │  │
│  │  └────────────────────────────────────────────┘  │  │
│  └───────────────────────────────────────────────────┘  │
│                                                         │
│  ┌───────────────────────────────────────────────────┐  │
│  │          File System                              │  │
│  │  • ~/RadarRecordings/ (Recording storage)         │  │
│  │  • ~/.irds/config/ (Configuration)                │  │
│  │  • ~/.irds/logs/ (Log files)                      │  │
│  └───────────────────────────────────────────────────┘  │
│                                                         │
│  ┌───────────────────────────────────────────────────┐  │
│  │        Network Interfaces                         │  │
│  │  • eth0: Radar data reception (UDP port 2025)     │  │
│  │  • lo: Simulation loopback                        │  │
│  └───────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
```

### 7.2 Network Deployment

```
┌──────────────────────────────────────────────────────────────┐
│                  Radar Network (10.0.1.0/24)                 │
│                                                              │
│  ┌────────────────┐         ┌────────────────┐              │
│  │ Radar System 1 │         │ Radar System 2 │              │
│  │  10.0.1.10     │         │  10.0.1.11     │              │
│  └────────┬───────┘         └────────┬───────┘              │
│           │ UDP                       │ UDP                  │
│           │ Port 2025                 │ Port 2025            │
│           │                           │                      │
│           └───────────┬───────────────┘                      │
│                       │                                      │
│                       ▼                                      │
│           ┌──────────────────────┐                           │
│           │   Network Switch     │                           │
│           └──────────┬───────────┘                           │
│                      │                                       │
│                      │                                       │
│                      ▼                                       │
│           ┌──────────────────────┐                           │
│           │   IRDS Workstation   │                           │
│           │     10.0.1.100       │                           │
│           └──────────────────────┘                           │
│                                                              │
└──────────────────────────────────────────────────────────────┘
```

### 7.3 Docker Deployment (Optional)

```
┌───────────────────────────────────────────────────────┐
│          Docker Host                                  │
│  ┌─────────────────────────────────────────────────┐  │
│  │        IRDS Container                           │  │
│  │  ┌───────────────────────────────────────────┐  │  │
│  │  │  IRDS Application                         │  │  │
│  │  │  • Qt Runtime                             │  │  │
│  │  │  • QGIS Libraries                         │  │  │
│  │  │  • Application Binary                     │  │  │
│  │  └───────────────────────────────────────────┘  │  │
│  │                                                 │  │
│  │  Volumes:                                       │  │
│  │  • /home/irds/RadarRecordings → Host volume    │  │
│  │  • /tmp/.X11-unix → X11 socket                 │  │
│  │                                                 │  │
│  │  Network:                                       │  │
│  │  • --net=host (access to host network)         │  │
│  └─────────────────────────────────────────────────┘  │
└───────────────────────────────────────────────────────┘
```

---

## 8. SECURITY ARCHITECTURE

### 8.1 Security Layers

```
┌──────────────────────────────────────────────────┐
│         Application Security                     │
│  • Input validation                              │
│  • Error handling                                │
│  • Safe coding practices                         │
└──────────────────────┬───────────────────────────┘
                       │
┌──────────────────────▼───────────────────────────┐
│         Data Security                            │
│  • File permissions (chmod 600 for sensitive)    │
│  • Access control (user/group permissions)       │
│  • Data validation                               │
└──────────────────────┬───────────────────────────┘
                       │
┌──────────────────────▼───────────────────────────┐
│         Network Security                         │
│  • Firewall rules (only port 2025/UDP)           │
│  • Network isolation                             │
│  • Input sanitization                            │
└──────────────────────┬───────────────────────────┘
                       │
┌──────────────────────▼───────────────────────────┐
│         System Security                          │
│  • User permissions                              │
│  • SELinux/AppArmor policies                     │
│  • System hardening                              │
└──────────────────────────────────────────────────┘
```

### 8.2 Security Measures

| Layer | Measure | Implementation |
|-------|---------|----------------|
| **Application** | Input Validation | Validate all user inputs before processing |
| **Application** | Error Handling | Try-catch blocks, graceful degradation |
| **Data** | File Permissions | Recording files: 644, Config files: 600 |
| **Data** | Access Control | User-specific directories (~/.irds/) |
| **Network** | Firewall | Only UDP port 2025 open |
| **Network** | Validation | Verify UDP packet format and content |
| **System** | Least Privilege | Run as non-root user |
| **System** | Logging | Security events logged to ~/.irds/logs/ |

---

## 9. PERFORMANCE ARCHITECTURE

### 9.1 Performance Requirements

| Metric | Requirement | Measurement |
|--------|-------------|-------------|
| **Track Update Rate** | ≥ 1 Hz | Tracks per second |
| **Map Render Rate** | ≥ 30 FPS | Frames per second |
| **UI Responsiveness** | < 100 ms | Click to response time |
| **Memory Usage** | < 2 GB | RAM consumption |
| **CPU Usage** | < 40% | Average CPU utilization |
| **Startup Time** | < 5 seconds | Application launch |

### 9.2 Performance Optimizations

#### 9.2.1 Threading Strategy

```
┌────────────────────────────────────────────────────┐
│               Main GUI Thread                      │
│  • UI rendering                                    │
│  • Event handling                                  │
│  • Widget updates                                  │
└────────────────────┬───────────────────────────────┘
                     │
         ┌───────────┼───────────┐
         │           │           │
         ▼           ▼           ▼
┌──────────────┐ ┌──────────────┐ ┌──────────────┐
│ UDP Receiver │ │ File I/O     │ │ Simulation   │
│   Thread     │ │  Thread      │ │   Thread     │
└──────────────┘ └──────────────┘ └──────────────┘
```

#### 9.2.2 Caching Strategy

- **Map Tiles:** Cached by QGIS for fast rendering
- **Track Symbols:** Pre-rendered and reused
- **Configuration:** Loaded once at startup

#### 9.2.3 Data Structure Optimization

- **QMap for tracks:** O(log n) lookup
- **QVector for lists:** Contiguous memory, fast iteration
- **Custom memory pools:** Reduce allocation overhead (future)

---

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                             │
│                          ZOPPLER SYSTEMS                                    │
│                      Integrated Radar Display System                        │
│                                                                             │
│  Document: Technical Architecture Document                                  │
│  Version: 1.0.0                                                            │
│  Date: October 13, 2025                                                    │
│  Classification: Confidential                                               │
│                                                                             │
│  © 2025 Zoppler Systems. All rights reserved.                             │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

**END OF DOCUMENT**
