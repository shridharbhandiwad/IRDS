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

# **SOFTWARE REQUIREMENTS SPECIFICATION**
## Integrated Radar Display System (IRDS)

---

**Document Information**

| Field | Value |
|-------|-------|
| **Document Title** | Software Requirements Specification |
| **Product Name** | Integrated Radar Display System (IRDS) |
| **Version** | 1.0.0 |
| **Date** | October 13, 2025 |
| **Status** | Approved |
| **Classification** | Confidential |
| **Organization** | Zoppler Systems |
| **Prepared By** | IRDS Development Team |
| **Approved By** | Chief Technology Officer |

---

## DOCUMENT CONTROL

### Revision History

| Version | Date | Author | Description |
|---------|------|--------|-------------|
| 1.0.0 | 2025-10-13 | IRDS Team | Initial release version |
| 0.9.0 | 2025-10-01 | IRDS Team | Draft for review |

### Distribution List

| Name | Role | Department |
|------|------|------------|
| Engineering Team | Development | Software Engineering |
| QA Team | Testing | Quality Assurance |
| Project Management | Oversight | PMO |
| Operations | Deployment | IT Operations |

---

## TABLE OF CONTENTS

1. [Introduction](#1-introduction)
2. [Overall Description](#2-overall-description)
3. [System Features](#3-system-features)
4. [External Interface Requirements](#4-external-interface-requirements)
5. [Non-Functional Requirements](#5-non-functional-requirements)
6. [Other Requirements](#6-other-requirements)
7. [Appendices](#7-appendices)

---

## 1. INTRODUCTION

### 1.1 Purpose

This Software Requirements Specification (SRS) document provides a complete description of the requirements for the Integrated Radar Display System (IRDS). It is intended for:

- Software developers implementing the system
- System testers validating the implementation
- Project managers planning and tracking development
- Stakeholders understanding system capabilities

### 1.2 Scope

The Integrated Radar Display System (IRDS) is a comprehensive radar data visualization and management platform designed to:

- **Display real-time radar tracks** with geographic context
- **Simulate radar targets** for training and testing
- **Record and replay** radar sessions
- **Monitor system health** of radar hardware and software components
- **Predict maintenance needs** using component lifecycle tracking
- **Analyze track data** with advanced analytics and charting

**Benefits:**
- Enhanced situational awareness for operators
- Reduced training costs through simulation capabilities
- Improved system reliability through predictive maintenance
- Comprehensive data recording for post-mission analysis

### 1.3 Definitions, Acronyms, and Abbreviations

| Term | Definition |
|------|------------|
| IRDS | Integrated Radar Display System |
| PPI | Plan Position Indicator |
| UDP | User Datagram Protocol |
| IFF | Identification Friend or Foe |
| QGIS | Quantum Geographic Information System |
| Qt | Cross-platform application framework |
| SRS | Software Requirements Specification |
| GUI | Graphical User Interface |
| API | Application Programming Interface |

### 1.4 References

- IEEE Std 830-1998: IEEE Recommended Practice for Software Requirements Specifications
- Qt 5.x Documentation: https://doc.qt.io/qt-5/
- QGIS API Documentation: https://qgis.org/api/
- Radar System Technical Specifications (Internal Document)

### 1.5 Overview

This document is organized as follows:
- **Section 2** provides overall system description
- **Section 3** details functional requirements
- **Section 4** specifies interface requirements
- **Section 5** defines non-functional requirements
- **Section 6** covers additional requirements
- **Section 7** contains appendices and supplementary information

---

## 2. OVERALL DESCRIPTION

### 2.1 Product Perspective

IRDS is a standalone desktop application that interfaces with radar hardware systems. It operates as the primary visualization and control interface for radar operators.

**System Context:**

```
┌─────────────────────────────────────────────────────┐
│              External Radar Systems                 │
│  (Transmit track data via UDP port 2025)           │
└────────────────┬────────────────────────────────────┘
                 │
                 │ UDP Network
                 │
┌────────────────▼────────────────────────────────────┐
│                                                     │
│         INTEGRATED RADAR DISPLAY SYSTEM             │
│                    (IRDS)                          │
│                                                     │
│  ┌─────────────────────────────────────────────┐  │
│  │  Display Engine  │  Data Processor          │  │
│  │  Analytics       │  Recording System        │  │
│  │  Health Monitor  │  Predictive Maintenance  │  │
│  └─────────────────────────────────────────────┘  │
│                                                     │
└────────────────┬────────────────────────────────────┘
                 │
                 │
┌────────────────▼────────────────────────────────────┐
│         File System (Recording Storage)             │
│              ~/RadarRecordings/                     │
└─────────────────────────────────────────────────────┘
```

### 2.2 Product Functions

Major system functions include:

1. **Real-Time Track Display**
   - Visualize radar tracks on geographic map
   - Display track attributes (heading, speed, identity)
   - Support multiple track types (Friend, Hostile, Unknown)

2. **Track Simulation**
   - Generate simulated radar tracks
   - Configurable parameters (range, azimuth, speed)
   - UDP transmission of simulated data

3. **Session Recording & Replay**
   - Record radar sessions to disk
   - Replay historical sessions
   - Variable playback speed control

4. **System Health Monitoring**
   - Monitor hardware component status
   - Track software module health
   - Performance metrics (CPU, memory, disk, network)

5. **Predictive Maintenance**
   - Component lifetime tracking
   - Maintenance schedule prediction
   - Automated recommendations

6. **Data Analytics**
   - Track statistics and analysis
   - Real-time charting
   - Performance metrics

### 2.3 User Classes and Characteristics

| User Class | Characteristics | Technical Expertise |
|------------|----------------|---------------------|
| **Radar Operators** | Primary system users; monitor real-time radar data | Medium |
| **Training Coordinators** | Use simulation features for operator training | Medium |
| **Maintenance Engineers** | Monitor system health and perform maintenance | High |
| **System Administrators** | Configure and manage IRDS deployment | High |
| **Analysts** | Review recorded sessions and analyze data | Medium-High |

### 2.4 Operating Environment

**Hardware Requirements:**
- Processor: Intel Core i5 or equivalent (minimum), i7 recommended
- RAM: 8 GB minimum, 16 GB recommended
- Storage: 500 GB minimum (for recordings)
- Graphics: Dedicated GPU with OpenGL 3.3+ support
- Network: Gigabit Ethernet

**Software Requirements:**
- Operating System: Linux (Ubuntu 20.04+ or equivalent)
- Qt Framework: 5.12 or higher
- QGIS Libraries: 3.x
- Additional libraries: GEOS, PROJ, SpatialIndex

### 2.5 Design and Implementation Constraints

- **Programming Language:** C++ (C++11 standard minimum)
- **GUI Framework:** Qt 5.x Widgets
- **Mapping Engine:** QGIS libraries
- **Network Protocol:** UDP for radar data transmission
- **File Format:** Binary format for recordings (.rdr)
- **Coordinate System:** WGS84 geographic coordinates

### 2.6 Assumptions and Dependencies

**Assumptions:**
- Network connectivity to radar systems is reliable
- Sufficient disk space available for recordings
- Operators have basic computer literacy
- System clock is synchronized (for accurate timestamps)

**Dependencies:**
- Qt 5.x framework availability
- QGIS libraries and dependencies
- Linux operating system with required kernel version
- Network infrastructure supporting UDP multicast

---

## 3. SYSTEM FEATURES

### 3.1 Real-Time Track Display

**Priority:** High  
**Description:** Display radar tracks on a geographic map in real-time.

#### 3.1.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| RTD-001 | System shall display tracks on a geographic map with appropriate symbols | High |
| RTD-002 | System shall update track positions at minimum 1 Hz rate | High |
| RTD-003 | System shall display track attributes (ID, heading, speed, altitude) | High |
| RTD-004 | System shall color-code tracks by identity (Friend=Green, Hostile=Red, Unknown=Yellow) | Medium |
| RTD-005 | System shall support zoom and pan operations on the map | High |
| RTD-006 | System shall display search beam pattern overlay | Medium |
| RTD-007 | System shall show PPI (Plan Position Indicator) layer | Medium |
| RTD-008 | System shall support track selection and highlighting | Medium |
| RTD-009 | System shall display track history trails (configurable) | Low |

### 3.2 Track Table Widget

**Priority:** High  
**Description:** Tabular display of all active tracks with detailed information.

#### 3.2.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| TT-001 | System shall display all active tracks in a sortable table | High |
| TT-002 | System shall show track ID, range, azimuth, heading, speed, altitude, identity | High |
| TT-003 | System shall update table at minimum 1 Hz rate | High |
| TT-004 | System shall allow sorting by any column | Medium |
| TT-005 | System shall highlight selected track in table and map | Medium |
| TT-006 | System shall display track count in status bar | Low |
| TT-007 | Track table shall be visible by default on startup | High |

### 3.3 Track Simulation

**Priority:** High  
**Description:** Generate simulated radar tracks for training and testing.

#### 3.3.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| SIM-001 | System shall generate tracks within configurable range (1-50 km) | High |
| SIM-002 | System shall distribute tracks across configurable azimuth spread (30-360°) | High |
| SIM-003 | System shall transmit simulated tracks via UDP to port 2025 | High |
| SIM-004 | System shall support configurable track count (1-50 tracks) | High |
| SIM-005 | System shall support configurable update rate (100-5000 ms) | High |
| SIM-006 | System shall support configurable speed range (min/max) | Medium |
| SIM-007 | System shall support track identity selection (Friend/Hostile/Unknown/Random) | Medium |
| SIM-008 | System shall support random movement option | Medium |
| SIM-009 | System shall provide Start/Pause/Stop/Reset controls | High |
| SIM-010 | System shall display real-time statistics (packets sent, simulation time, CPU usage) | Medium |
| SIM-011 | System shall display live track table of all simulated tracks | Medium |

### 3.4 Session Recording

**Priority:** High  
**Description:** Record radar sessions to disk for later analysis.

#### 3.4.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| REC-001 | System shall record all track data to binary files (.rdr format) | High |
| REC-002 | System shall support pause/resume during recording | High |
| REC-003 | System shall automatically create recording directory (~/RadarRecordings/) | High |
| REC-004 | System shall display recording duration and frame count during recording | Medium |
| REC-005 | System shall save recordings with timestamp-based filenames | Medium |
| REC-006 | System shall provide recording library management interface | Medium |
| REC-007 | System shall display recording file size and date | Low |
| REC-008 | System shall support export of recordings to different locations | Medium |
| REC-009 | System shall support deletion of recordings from library | Medium |

### 3.5 Session Replay

**Priority:** High  
**Description:** Replay recorded radar sessions.

#### 3.5.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| REP-001 | System shall load and replay saved recordings | High |
| REP-002 | System shall support multiple playback speeds (0.25x, 0.5x, 1x, 2x, 4x) | High |
| REP-003 | System shall support pause/resume during replay | High |
| REP-004 | System shall display progress indicator (current frame / total frames) | Medium |
| REP-005 | System shall inject replayed tracks into display system | High |
| REP-006 | System shall support frame-by-frame playback control | Low |
| REP-007 | System shall handle replay completion automatically | Medium |

### 3.6 Health Monitoring

**Priority:** High  
**Description:** Monitor health status of hardware and software components.

#### 3.6.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| HM-001 | System shall monitor 6 hardware modules (Radar, Servo, Power, RF, Thermal, Storage) | High |
| HM-002 | System shall monitor 6 software modules (Display, Processor, Network, Analytics, Security, Database) | High |
| HM-003 | System shall calculate overall system health percentage (0-100%) | High |
| HM-004 | System shall display 6 health status levels (Excellent, Good, Fair, Poor, Service Required, Critical) | High |
| HM-005 | System shall monitor system performance (CPU, Memory, Disk, Network usage) | High |
| HM-006 | System shall display color-coded status indicators | Medium |
| HM-007 | System shall track system uptime | Low |
| HM-008 | System shall maintain alert system with severity levels | Medium |
| HM-009 | System shall provide module detail view on click | Medium |
| HM-010 | System shall auto-refresh health data every 5 seconds | Medium |
| HM-011 | System shall support running diagnostics function | Medium |
| HM-012 | System shall export health report in TXT format | Low |

### 3.7 Predictive Maintenance

**Priority:** High  
**Description:** Predict maintenance needs using component lifecycle tracking.

#### 3.7.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| PM-001 | System shall monitor 12 components for maintenance prediction | High |
| PM-002 | System shall track component lifetime percentage (0-100%) | High |
| PM-003 | System shall calculate days until maintenance needed | High |
| PM-004 | System shall track operating hours for each component | Medium |
| PM-005 | System shall record last maintenance date | Medium |
| PM-006 | System shall display 6 maintenance status levels (Excellent to Critical) | High |
| PM-007 | System shall provide sortable component list by urgency | Medium |
| PM-008 | System shall display maintenance schedule table (60-day view) | Medium |
| PM-009 | System shall show priority indicators (Critical/High/Medium/Low) | Medium |
| PM-010 | System shall classify maintenance types (Emergency/Preventive/Routine) | Medium |
| PM-011 | System shall generate AI-style recommendations | Low |
| PM-012 | System shall provide schedule maintenance interface | Medium |
| PM-013 | System shall support viewing maintenance history | Low |
| PM-014 | System shall export maintenance report in TXT format | Low |
| PM-015 | System shall auto-refresh every 10 seconds | Medium |

### 3.8 Analytics

**Priority:** Medium  
**Description:** Analyze track data with statistics and visualizations.

#### 3.8.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| AN-001 | System shall display track count statistics | Medium |
| AN-002 | System shall show track distribution by identity | Medium |
| AN-003 | System shall calculate and display average speeds | Low |
| AN-004 | System shall provide real-time charts and graphs | Medium |
| AN-005 | System shall support data export for external analysis | Low |

### 3.9 Charts Widget

**Priority:** Medium  
**Description:** Display real-time charts of system and track data.

#### 3.9.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| CH-001 | System shall display charts in bottom dock area | Medium |
| CH-002 | System shall limit chart widget height (250-350px) | Low |
| CH-003 | System shall be hidden by default | Low |
| CH-004 | System shall support time-series data visualization | Medium |

### 3.10 Configuration Panel

**Priority:** High  
**Description:** Configure display and system parameters.

#### 3.10.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| CFG-001 | System shall provide interface for display configuration | High |
| CFG-002 | System shall allow adjustment of map layers | Medium |
| CFG-003 | System shall support color scheme customization | Low |
| CFG-004 | System shall save user preferences | Medium |

---

## 4. EXTERNAL INTERFACE REQUIREMENTS

### 4.1 User Interface Requirements

#### 4.1.1 General UI Requirements

| ID | Requirement |
|----|-------------|
| UI-001 | System shall use dark theme design for reduced eye strain |
| UI-002 | System shall provide keyboard shortcuts for all major functions |
| UI-003 | System shall display status bar with system information |
| UI-004 | System shall support dockable/floatable widgets |
| UI-005 | System shall maintain consistent color coding (Green=Good, Yellow=Warning, Red=Critical) |

#### 4.1.2 Keyboard Shortcuts

| Shortcut | Function |
|----------|----------|
| H | Map Home (reset view) |
| T | Toggle Track Table |
| C | Toggle Config Panel |
| I | Toggle Interfaces Panel |
| A | Toggle Analytics Widget |
| S | Toggle Simulation Widget |
| R | Toggle Recording Widget |
| M | Toggle Health Monitor |
| P | Toggle Predictive Maintenance |

#### 4.1.3 Layout Requirements

- Central widget: Map display canvas
- Left dock: Config, Interfaces, Simulation, Recording (tabbed)
- Right dock: Track Table (default), Analytics, Health Monitor, Predictive Maintenance (tabbed)
- Bottom dock: Charts widget (hidden by default)

### 4.2 Hardware Interface Requirements

| ID | Requirement |
|----|-------------|
| HW-001 | System shall interface with radar hardware via UDP network protocol |
| HW-002 | System shall receive track data on UDP port 2025 |
| HW-003 | System shall support standard Ethernet network interfaces |
| HW-004 | System shall utilize GPU for map rendering acceleration |

### 4.3 Software Interface Requirements

| ID | Requirement |
|----|-------------|
| SW-001 | System shall use Qt 5.x framework for GUI components |
| SW-002 | System shall use QGIS libraries for map rendering |
| SW-003 | System shall use Qt Network module for UDP communication |
| SW-004 | System shall use Qt Charts module for data visualization |
| SW-005 | System shall store recordings in binary format using Qt DataStream |

### 4.4 Communication Interface Requirements

| ID | Requirement |
|----|-------------|
| COM-001 | System shall receive track data via UDP protocol |
| COM-002 | System shall transmit simulated tracks via UDP to localhost:2025 |
| COM-003 | System shall handle network packet loss gracefully |
| COM-004 | System shall support network bandwidth up to 1 Gbps |

---

## 5. NON-FUNCTIONAL REQUIREMENTS

### 5.1 Performance Requirements

| ID | Requirement | Metric |
|----|-------------|--------|
| PERF-001 | Track display update rate | Minimum 1 Hz, target 10 Hz |
| PERF-002 | Maximum track capacity | 50 simultaneous tracks |
| PERF-003 | Map rendering frame rate | Minimum 30 FPS |
| PERF-004 | Simulation update latency | < 100 ms |
| PERF-005 | Recording write latency | < 50 ms per frame |
| PERF-006 | UI responsiveness | < 100 ms for user actions |
| PERF-007 | Memory footprint | < 2 GB RAM for normal operation |
| PERF-008 | CPU utilization | < 40% on recommended hardware |

### 5.2 Safety Requirements

| ID | Requirement |
|----|-------------|
| SAFE-001 | System shall not interfere with radar hardware operation |
| SAFE-002 | System shall validate all user inputs to prevent crashes |
| SAFE-003 | System shall handle file system errors gracefully |
| SAFE-004 | System shall prevent data corruption during recording |

### 5.3 Security Requirements

| ID | Requirement |
|----|-------------|
| SEC-001 | System shall run with minimal required privileges |
| SEC-002 | System shall validate network data before processing |
| SEC-003 | System shall protect recording files from unauthorized access |
| SEC-004 | System shall log security-relevant events |

### 5.4 Software Quality Attributes

#### 5.4.1 Reliability

| ID | Requirement |
|----|-------------|
| REL-001 | System shall have MTBF (Mean Time Between Failures) > 720 hours |
| REL-002 | System shall automatically recover from non-critical errors |
| REL-003 | System shall maintain data integrity during crashes |

#### 5.4.2 Maintainability

| ID | Requirement |
|----|-------------|
| MAIN-001 | Code shall follow C++ coding standards |
| MAIN-002 | All functions shall be documented with Doxygen comments |
| MAIN-003 | Code shall have modular architecture for easy updates |
| MAIN-004 | System shall log all errors for troubleshooting |

#### 5.4.3 Usability

| ID | Requirement |
|----|-------------|
| USE-001 | New operators shall be productive within 2 hours of training |
| USE-002 | All functions shall be accessible via keyboard or mouse |
| USE-003 | System shall provide helpful error messages |
| USE-004 | UI shall use intuitive icons and labels |

#### 5.4.4 Portability

| ID | Requirement |
|----|-------------|
| PORT-001 | System shall run on multiple Linux distributions |
| PORT-002 | System shall support both x86_64 and ARM architectures |
| PORT-003 | System shall minimize platform-specific code |

---

## 6. OTHER REQUIREMENTS

### 6.1 Database Requirements

| ID | Requirement |
|----|-------------|
| DB-001 | System shall use file-based storage for recordings |
| DB-002 | Recording format shall be versioned for future compatibility |
| DB-003 | System shall maintain recording metadata (date, duration, frame count) |

### 6.2 Internationalization Requirements

| ID | Requirement |
|----|-------------|
| I18N-001 | System shall use UTF-8 encoding for all text |
| I18N-002 | UI strings shall be separated for future translation |
| I18N-003 | System shall support international date/time formats |

### 6.3 Legal Requirements

| ID | Requirement |
|----|-------------|
| LEG-001 | System shall comply with all applicable open-source licenses |
| LEG-002 | System shall include copyright notices for all third-party components |
| LEG-003 | System shall not violate any software patents |

---

## 7. APPENDICES

### 7.1 Appendix A: Track Data Format

Track data received via UDP contains the following fields:

```cpp
struct TrackData {
    int32_t trackId;          // Unique track identifier
    double latitude;          // WGS84 latitude (degrees)
    double longitude;         // WGS84 longitude (degrees)
    double altitude;          // Altitude (meters)
    double heading;           // Heading (degrees, 0-360)
    double speed;             // Speed (m/s)
    int32_t identity;         // IFF: 1=Friend, 2=Hostile, 3=Unknown
    uint64_t timestamp;       // Unix timestamp (milliseconds)
};
```

### 7.2 Appendix B: Recording File Format

Recording files (.rdr) use the following structure:

```
[Header]
- Magic Number: "RADAR_RECORDING_V1" (18 bytes)
- Version: uint32
- Start Timestamp: uint64
- Frame Count: uint32

[Frames]
- Frame Timestamp: uint64
- Track Count: uint32
- Track Data: TrackData[Track Count]
```

### 7.3 Appendix C: Health Status Thresholds

| Status | Percentage Range | Color |
|--------|-----------------|-------|
| Excellent | 90-100% | Green (#4ade80) |
| Good | 75-89% | Light Green (#10b981) |
| Fair | 60-74% | Yellow (#fbbf24) |
| Poor | 40-59% | Orange (#fb923c) |
| Service Required | 20-39% | Red-Orange (#f97316) |
| Critical | 0-19% | Red (#ef4444) |

### 7.4 Appendix D: Maintenance Priority Classification

| Priority | Days Until Maintenance | Color | Action |
|----------|----------------------|-------|--------|
| Critical | 0 | Red | Immediate service |
| High | 1-7 days | Orange | Schedule urgently |
| Medium | 8-30 days | Yellow | Plan maintenance |
| Low | 31+ days | Green | Monitor status |

---

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                             │
│                          ZOPPLER SYSTEMS                                    │
│                      Integrated Radar Display System                        │
│                                                                             │
│  Document: Software Requirements Specification                              │
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
