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

# **USER MANUAL**
## Integrated Radar Display System (IRDS)

---

**Document Information**

| Field | Value |
|-------|-------|
| **Document Title** | User Manual |
| **Product Name** | Integrated Radar Display System (IRDS) |
| **Version** | 1.0.0 |
| **Date** | October 13, 2025 |
| **Status** | Approved |
| **Classification** | For Official Use |
| **Organization** | Zoppler Systems |
| **Prepared By** | Documentation Team |
| **Target Audience** | Radar Operators, Trainers, Analysts |

---

## DOCUMENT CONTROL

### Revision History

| Version | Date | Author | Description |
|---------|------|--------|-------------|
| 1.0.0 | 2025-10-13 | Doc Team | Initial release version |

---

## TABLE OF CONTENTS

1. [Introduction](#1-introduction)
2. [Getting Started](#2-getting-started)
3. [User Interface Overview](#3-user-interface-overview)
4. [Track Display Operations](#4-track-display-operations)
5. [Track Simulation](#5-track-simulation)
6. [Recording & Replay](#6-recording--replay)
7. [System Health Monitoring](#7-system-health-monitoring)
8. [Predictive Maintenance](#8-predictive-maintenance)
9. [Analytics & Charts](#9-analytics--charts)
10. [Configuration](#10-configuration)
11. [Troubleshooting](#11-troubleshooting)
12. [Quick Reference](#12-quick-reference)

---

## 1. INTRODUCTION

### 1.1 Welcome

Welcome to the Integrated Radar Display System (IRDS) User Manual. This guide provides comprehensive instructions for operating IRDS effectively.

### 1.2 About IRDS

IRDS is a professional radar display and management system designed for:

- **Real-time radar track visualization**
- **Training through simulation**
- **Session recording and analysis**
- **System health monitoring**
- **Predictive maintenance management**

### 1.3 Who Should Use This Manual

This manual is intended for:

- **Radar Operators** - Primary system users
- **Training Coordinators** - Simulation and training operations
- **Maintenance Engineers** - System health and maintenance
- **Analysts** - Data analysis and review

### 1.4 Manual Conventions

| Convention | Meaning |
|------------|---------|
| **Bold** | Important terms, buttons, menu items |
| `Monospace` | File paths, code, keyboard keys |
| 🎯 Icon | Tips and best practices |
| ⚠️ Icon | Warnings and cautions |
| ℹ️ Icon | Additional information |

### 1.5 Safety Information

⚠️ **IMPORTANT SAFETY NOTICE**

- Do not interrupt system operations during critical radar tracking
- Ensure proper training before operating in live radar environments
- Follow all organizational safety and security protocols
- Report system anomalies immediately to technical support

---

## 2. GETTING STARTED

### 2.1 System Requirements

**Minimum Requirements:**
- Processor: Intel Core i5 or equivalent
- RAM: 8 GB
- Storage: 500 GB
- Graphics: GPU with OpenGL 3.3+ support
- Network: Gigabit Ethernet
- OS: Linux (Ubuntu 20.04+)

**Recommended Requirements:**
- Processor: Intel Core i7 or better
- RAM: 16 GB
- Storage: 1 TB SSD
- Graphics: Dedicated GPU with 2GB+ VRAM
- Network: Dedicated network interface for radar data

### 2.2 Starting IRDS

**Method 1: Desktop Launcher**
1. Locate IRDS icon on desktop
2. Double-click to launch

**Method 2: Terminal**
```bash
cd /path/to/installation
./bin/RadarDisplay
```

### 2.3 First Launch

On first launch, IRDS will:

1. Initialize all system components
2. Create necessary directories (~/.RadarRecordings/)
3. Load default configuration
4. Display main window with Track Table visible

**Default Layout:**
- **Center:** Map display
- **Right:** Track Table (visible by default)
- **Left:** Configuration panels (minimized)
- **Bottom:** Charts (hidden)

### 2.4 Logging Out

**To exit IRDS:**

1. **File → Exit** or
2. Close button (X) on window or
3. Press `Alt+F4`

⚠️ **Note:** Active recordings will be stopped and saved automatically.

---

## 3. USER INTERFACE OVERVIEW

### 3.1 Main Window Layout

```
┌─────────────────────────────────────────────────────────────┐
│  File  Edit  View  Tools  Help                             │
├────────────┬────────────────────────────┬────────────────────┤
│            │                            │                    │
│   Left     │                            │      Right         │
│   Panels   │      Map Display           │      Panels        │
│            │                            │                    │
│  • Config  │   [Geographic Map with     │  • Track Table ⭐  │
│  • Inter-  │    Radar Tracks]           │  • Analytics       │
│    faces   │                            │  • Health          │
│  • Simul-  │                            │  • Maintenance     │
│    ation   │                            │                    │
│  • Record  │                            │                    │
│            │                            │                    │
├────────────┴────────────────────────────┴────────────────────┤
│  Status Bar: Track Count | Shortcuts | System Status        │
└──────────────────────────────────────────────────────────────┘
```

### 3.2 Keyboard Shortcuts

| Key | Widget | Function |
|-----|--------|----------|
| `H` | Map | Reset to home view |
| `T` | Track Table | Show/hide track table |
| `C` | Config Panel | Show/hide configuration |
| `I` | Interfaces | Show/hide interfaces panel |
| `A` | Analytics | Show/hide analytics widget |
| `S` | Simulation | Show/hide simulation widget |
| `R` | Recording | Show/hide recording widget |
| `M` | Health Monitor | Show/hide health monitor |
| `P` | Maintenance | Show/hide predictive maintenance |

🎯 **TIP:** Memorize these shortcuts for faster operation!

### 3.3 Status Bar

The status bar displays:

- **Track Count:** Number of active tracks
- **Shortcuts:** Quick reference to keyboard shortcuts
- **System Status:** Current system state
- **Time:** Current system time

### 3.4 Dock Widgets

All panels are **dockable widgets** that can be:

- **Moved:** Drag title bar to reposition
- **Floated:** Double-click title bar to float/dock
- **Tabbed:** Drag onto another widget to create tabs
- **Resized:** Drag edges to resize
- **Closed:** Click X button to close (reopen with keyboard shortcuts)

---

## 4. TRACK DISPLAY OPERATIONS

### 4.1 Understanding the Track Display

The central map display shows:

- **Base Map:** Geographic context (streets, terrain)
- **Track Symbols:** Radar targets with directional indicators
- **Search Beam:** Rotating radar beam pattern (optional)
- **PPI Display:** Plan Position Indicator overlay (optional)
- **Range Rings:** Distance reference circles (optional)

### 4.2 Track Symbols

| Symbol Color | Identity | Description |
|-------------|----------|-------------|
| 🟢 Green | Friend | Friendly/Allied track |
| 🔴 Red | Hostile | Hostile/Threat track |
| 🟡 Yellow | Unknown | Unknown/Unidentified track |

**Track Symbol Components:**
- **Triangle:** Track position and heading direction
- **Line:** Track history trail (if enabled)
- **Label:** Track ID number

### 4.3 Map Navigation

**Zoom:**
- **Mouse Wheel:** Scroll up/down to zoom in/out
- **Keyboard:** `+` to zoom in, `-` to zoom out

**Pan:**
- **Left Click + Drag:** Pan map in any direction
- **Arrow Keys:** Pan map using keyboard

**Home View:**
- Press `H` to reset map to default view
- Centers on radar location with optimal zoom

### 4.4 Track Selection

**To select a track:**

1. **Click** on track symbol on map, or
2. **Click** on track row in Track Table

**When selected:**
- Track highlights on map
- Corresponding row highlights in Track Table
- Track details appear in Analytics widget (if visible)

### 4.5 Track Information

Each track displays:

| Attribute | Description |
|-----------|-------------|
| **Track ID** | Unique identifier |
| **Range** | Distance from radar (meters) |
| **Azimuth** | Bearing from radar (degrees) |
| **Heading** | Direction of travel (degrees) |
| **Speed** | Ground speed (m/s or knots) |
| **Altitude** | Height above sea level (meters) |
| **Identity** | Friend/Hostile/Unknown |

---

## 5. TRACK SIMULATION

### 5.1 Opening the Simulation Widget

**Method 1:** Press `S` key  
**Method 2:** View → Simulation Widget

### 5.2 Simulation Controls

```
┌─────────────────────────────────────────────────┐
│         TRACK SIMULATION                        │
├─────────────────────────────────────────────────┤
│  [ ▶ Start ]  [ ⏸ Pause ]  [ ⏹ Stop ]  [↻ Reset] │
├─────────────────────────────────────────────────┤
│  Configuration                                  │
│  • Number of Tracks: [  5  ]                   │
│  • Max Range (km):   [ 10  ]                   │
│  • Update Rate (ms): [ 1000 ]                  │
│  • Azimuth Spread:   [ 360° ]                  │
│  • Speed Min (m/s):  [ 50  ]                   │
│  • Speed Max (m/s):  [ 150 ]                   │
│  • Identity:         [ Random ▼ ]              │
│  • ☑ Random Movement                           │
├─────────────────────────────────────────────────┤
│  Statistics                                     │
│  • Active Tracks:    5                         │
│  • Packets Sent:     1,234                     │
│  • Simulation Time:  00:20:34                  │
│  • CPU Usage:        23%                       │
└─────────────────────────────────────────────────┘
```

### 5.3 Configuring a Simulation

#### 5.3.1 Number of Tracks

- **Range:** 1-50 tracks
- **Default:** 5 tracks
- **Recommendation:** Start with 5-10 for training

#### 5.3.2 Maximum Range

- **Range:** 1-50 kilometers
- **Default:** 10 km
- **Purpose:** Defines area where tracks are generated

ℹ️ **Note:** Tracks distribute randomly within 0.3 to 1.0 × Max Range

#### 5.3.3 Update Rate

- **Range:** 100-5000 milliseconds
- **Default:** 1000 ms (1 Hz)
- **Lower values:** More frequent updates, higher CPU usage
- **Higher values:** Less frequent updates, lower CPU usage

#### 5.3.4 Azimuth Spread

- **Range:** 30-360 degrees
- **Default:** 360° (full circle)
- **Example:** 90° spreads tracks in a quarter-circle sector

#### 5.3.5 Speed Range

- **Min Speed:** Minimum track speed (m/s)
- **Max Speed:** Maximum track speed (m/s)
- **Default:** 50-150 m/s
- **Tracks:** Assigned random speeds within this range

#### 5.3.6 Track Identity

| Option | Behavior |
|--------|----------|
| **Friend** | All tracks friendly (green) |
| **Hostile** | All tracks hostile (red) |
| **Unknown** | All tracks unknown (yellow) |
| **Random** | Mixed identities (recommended for training) |

#### 5.3.7 Random Movement

- **Enabled:** Tracks change heading/speed randomly
- **Disabled:** Tracks maintain constant heading/speed
- **Recommendation:** Enable for realistic scenarios

### 5.4 Running a Simulation

**Step-by-Step:**

1. **Configure parameters** (see Section 5.3)
2. **Click ▶ Start button**
3. **Observe tracks** appearing on map
4. **Monitor statistics** in real-time

**To pause:**
- Click **⏸ Pause** button
- Simulation freezes, can resume

**To stop:**
- Click **⏹ Stop** button
- Simulation ends, all simulated tracks removed

**To reset:**
- Click **↻ Reset** button
- Clears all tracks, resets statistics

### 5.5 Simulation Examples

#### Example 1: Basic Training Scenario
```
Number of Tracks: 5
Max Range: 10 km
Update Rate: 1000 ms
Azimuth Spread: 360°
Speed: 50-150 m/s
Identity: Random
Random Movement: ✓
```

#### Example 2: Threat Approach Scenario
```
Number of Tracks: 10
Max Range: 20 km
Update Rate: 500 ms
Azimuth Spread: 90° (from north)
Speed: 100-200 m/s
Identity: Hostile
Random Movement: ✗
```

#### Example 3: High-Density Traffic
```
Number of Tracks: 30
Max Range: 15 km
Update Rate: 1000 ms
Azimuth Spread: 360°
Speed: 30-100 m/s
Identity: Random
Random Movement: ✓
```

---

## 6. RECORDING & REPLAY

### 6.1 Opening the Recording Widget

**Method 1:** Press `R` key  
**Method 2:** View → Recording Widget

### 6.2 Recording Widget Layout

```
┌─────────────────────────────────────────────────┐
│           RECORDING & REPLAY                    │
├─────────────────────────────────────────────────┤
│  Recording                                      │
│  [ ● Record ]  [ ⏸ Pause ]  [ ⏹ Stop ]         │
│  Duration: 00:00:00  |  Frames: 0              │
├─────────────────────────────────────────────────┤
│  Replay                                         │
│  File: [ Select recording... ▼ ]               │
│  [ ▶ Play ]  [ ⏸ Pause ]  [ ⏹ Stop ]           │
│  Speed: [ 1.0x ▼ ]                             │
│  Progress: [████░░░░░░░░] 40%                  │
│  Frame: 240 / 600                               │
├─────────────────────────────────────────────────┤
│  Recording Library                              │
│  ┌───────────────────────────────────────────┐ │
│  │ recording_20251013_143022.rdr  |  45 MB   │ │
│  │ recording_20251012_091545.rdr  |  89 MB   │ │
│  │ recording_20251011_163211.rdr  |  32 MB   │ │
│  └───────────────────────────────────────────┘ │
│  [ 🗑 Delete ]  [ 💾 Export ]  [ ↻ Refresh ]    │
└─────────────────────────────────────────────────┘
```

### 6.3 Recording a Session

**To start recording:**

1. Open Recording Widget (`R` key)
2. Click **● Record** button
3. Recording begins immediately

**During recording:**
- **Duration** shows elapsed time
- **Frames** shows number of frames recorded
- All tracks are captured at 1 Hz rate

**To pause recording:**
- Click **⏸ Pause** button
- Recording pauses, timer stops
- Click **● Record** again to resume

**To stop recording:**
- Click **⏹ Stop** button
- Recording stops and saves automatically
- File saved to `~/RadarRecordings/` directory
- Filename format: `recording_YYYYMMDD_HHMMSS.rdr`

### 6.4 Recording Best Practices

🎯 **BEST PRACTICES:**

1. **Before Recording:**
   - Ensure sufficient disk space (1 MB per minute approximate)
   - Verify ~/RadarRecordings/ directory exists
   - Clear old recordings if needed

2. **During Recording:**
   - Avoid closing IRDS application
   - Monitor disk space
   - Note any significant events (for later analysis)

3. **After Recording:**
   - Verify file appears in Recording Library
   - Check file size is reasonable
   - Test replay immediately to confirm quality

### 6.5 Replaying a Session

**To replay a recording:**

1. Open Recording Widget (`R` key)
2. **Select recording** from File dropdown
3. **Choose playback speed** (0.25x, 0.5x, 1x, 2x, 4x)
4. Click **▶ Play** button

**During replay:**
- Tracks appear on map as if live
- Progress bar shows playback position
- Frame counter displays current/total frames

**Playback speeds:**

| Speed | Description | Use Case |
|-------|-------------|----------|
| **0.25x** | Quarter speed | Detailed analysis |
| **0.5x** | Half speed | Careful review |
| **1x** | Real-time | Normal playback |
| **2x** | Double speed | Quick review |
| **4x** | Quadruple speed | Fast forward |

**To pause replay:**
- Click **⏸ Pause** button
- Replay pauses at current frame
- Click **▶ Play** to resume

**To stop replay:**
- Click **⏹ Stop** button
- Replay stops, clears tracks from map

### 6.6 Managing Recordings

#### 6.6.1 Recording Library

The Recording Library shows all saved recordings with:
- **Filename:** Date and time of recording
- **File Size:** Storage space used
- **Date:** Creation date

#### 6.6.2 Deleting Recordings

**To delete a recording:**

1. Select recording in library
2. Click **🗑 Delete** button
3. Confirm deletion in dialog

⚠️ **WARNING:** Deleted recordings cannot be recovered!

#### 6.6.3 Exporting Recordings

**To export a recording:**

1. Select recording in library
2. Click **💾 Export** button
3. Choose destination folder
4. Recording copied to selected location

**Use cases:**
- Archive important sessions
- Share recordings with analysts
- Backup to external storage

#### 6.6.4 Refreshing the Library

- Click **↻ Refresh** button to update library
- Useful after manually adding/removing recording files

---

## 7. SYSTEM HEALTH MONITORING

### 7.1 Opening Health Monitor

**Method 1:** Press `M` key  
**Method 2:** View → Health Monitor

### 7.2 Health Monitor Overview

```
┌─────────────────────────────────────────────────┐
│          SYSTEM HEALTH MONITOR                  │
├─────────────────────────────────────────────────┤
│  Overall System Health: 87%  [GOOD]             │
│  Uptime: 48 hours 23 minutes                    │
│  Last Check: 2025-10-13 14:30:22                │
├─────────────────────────────────────────────────┤
│  Hardware Modules                               │
│  ┌──────────┐ ┌──────────┐ ┌──────────┐       │
│  │ 🎯 Radar │ │ ⚙️ Servo │ │ 🔋 Power │       │
│  │   92%    │ │   88%    │ │   95%    │       │
│  │ EXCELLENT│ │  GOOD    │ │ EXCELLENT│       │
│  └──────────┘ └──────────┘ └──────────┘       │
│                                                 │
│  Software Modules                               │
│  ┌──────────┐ ┌──────────┐ ┌──────────┐       │
│  │🖥️Display │ │ 🧠Process│ │ 🌐Network│       │
│  │   89%    │ │   91%    │ │   85%    │       │
│  │  GOOD    │ │ EXCELLENT│ │  GOOD    │       │
│  └──────────┘ └──────────┘ └──────────┘       │
├─────────────────────────────────────────────────┤
│  System Performance                             │
│  CPU:    [████████░░] 35%                      │
│  Memory: [██████░░░░] 60%                      │
│  Disk:   [████░░░░░░] 40%                      │
│  Network:[███░░░░░░░] 25%                      │
├─────────────────────────────────────────────────┤
│  System Alerts (2)                              │
│  ⚠️  Thermal System - Temperature elevated      │
│  ℹ️  Database Manager - Maintenance recommended │
├─────────────────────────────────────────────────┤
│  [ 🔍 Run Diagnostics ]  [ 📄 Export Report ]   │
└─────────────────────────────────────────────────┘
```

### 7.3 Health Status Levels

| Status | Range | Color | Meaning |
|--------|-------|-------|---------|
| **Excellent** | 90-100% | 🟢 Green | Optimal operation |
| **Good** | 75-89% | 🟢 Light Green | Normal operation |
| **Fair** | 60-74% | 🟡 Yellow | Monitor closely |
| **Poor** | 40-59% | 🟠 Orange | Service recommended |
| **Service Required** | 20-39% | 🟠 Red-Orange | Immediate attention |
| **Critical** | 0-19% | 🔴 Red | System failure imminent |

### 7.4 Hardware Modules

| Module | Description | Monitored Parameters |
|--------|-------------|---------------------|
| **🎯 Radar Unit** | Main radar transceiver | Signal strength, calibration |
| **⚙️ Servo Controller** | Antenna positioning | Position accuracy, response time |
| **🔋 Power Supply** | Power distribution | Voltage, current, stability |
| **📡 RF Transceiver** | RF communication | Signal quality, noise level |
| **🌡️ Thermal System** | Cooling and temperature | Temperature, fan speed |
| **💾 Data Storage** | Storage systems | Disk health, I/O performance |

### 7.5 Software Modules

| Module | Description | Monitored Parameters |
|--------|-------------|---------------------|
| **🖥️ Display Engine** | Graphics rendering | Frame rate, rendering errors |
| **🧠 Data Processor** | Track processing | Processing latency, errors |
| **🌐 Network Stack** | Network communication | Packet loss, latency |
| **📊 Analytics Engine** | Data analysis | Processing speed, accuracy |
| **🔐 Security Module** | Security features | Threat detection, integrity |
| **🗂️ Database Manager** | Data storage | Query performance, integrity |

### 7.6 Viewing Module Details

**To view detailed information:**

1. **Click on any module card**
2. **Detail dialog appears** showing:
   - Component name
   - Current health percentage
   - Last check time
   - Specific metrics
   - Recommendations (if any)

### 7.7 System Performance Metrics

The Health Monitor tracks real-time system performance:

**CPU Usage:**
- Shows current CPU utilization
- Color-coded: Green (<50%), Yellow (50-80%), Red (>80%)

**Memory Usage:**
- Shows current RAM utilization
- Includes swap usage if applicable

**Disk Usage:**
- Shows storage space utilization
- Monitors I/O performance

**Network Usage:**
- Shows network bandwidth utilization
- Tracks packet statistics

### 7.8 System Alerts

Alerts are classified by severity:

| Icon | Severity | Description |
|------|----------|-------------|
| 🔴 | Critical | Immediate action required |
| ⚠️ | Warning | Attention needed soon |
| ℹ️ | Info | Informational notice |

### 7.9 Running Diagnostics

**To run system diagnostics:**

1. Click **🔍 Run Diagnostics** button
2. Comprehensive system check executes
3. Results appear in alerts table
4. Overall health percentage updates

**Diagnostics include:**
- Hardware communication tests
- Software module integrity checks
- Performance benchmarks
- Configuration validation

🎯 **RECOMMENDATION:** Run diagnostics weekly or after system updates.

### 7.10 Exporting Health Reports

**To export a health report:**

1. Click **📄 Export Report** button
2. Choose save location
3. Report saved as text file

**Report includes:**
- Overall system health
- All module statuses
- Performance metrics
- Active alerts
- Timestamp and system info

---

## 8. PREDICTIVE MAINTENANCE

### 8.1 Opening Predictive Maintenance

**Method 1:** Press `P` key  
**Method 2:** View → Predictive Maintenance

### 8.2 Predictive Maintenance Overview

```
┌─────────────────────────────────────────────────┐
│       PREDICTIVE MAINTENANCE                    │
├─────────────────────────────────────────────────┤
│  System Condition: 82%  [GOOD]                  │
│  Next Maintenance: 45 days                      │
│  Critical Components: 1                         │
├─────────────────────────────────────────────────┤
│  Component Status (sortable)                    │
│  ┌─────────────────────────────────────────┐   │
│  │Component          │Condition│Days│Status│   │
│  ├─────────────────────────────────────────┤   │
│  │Backup Battery     │  35%    │ 3  │🔴CRIT│   │
│  │Servo Motors       │  68%    │ 28 │🟡FAIR│   │
│  │RF Transmitter     │  75%    │ 42 │🟢GOOD│   │
│  │Radar Antenna Array│  88%    │ 67 │🟢GOOD│   │
│  │Power Supply Unit  │  92%    │ 85 │✅EXC │   │
│  └─────────────────────────────────────────┘   │
├─────────────────────────────────────────────────┤
│  Upcoming Maintenance Schedule (60 days)        │
│  ┌─────────────────────────────────────────┐   │
│  │Date      │Component        │Priority    │   │
│  ├─────────────────────────────────────────┤   │
│  │Oct 16    │Backup Battery   │CRITICAL    │   │
│  │Oct 28    │Servo Motors     │HIGH        │   │
│  │Nov 24    │RF Transmitter   │MEDIUM      │   │
│  └─────────────────────────────────────────┘   │
├─────────────────────────────────────────────────┤
│  Recommendations                                │
│  • URGENT: Replace backup battery within 3 days│
│  • Schedule servo motor lubrication in 28 days │
│  • Monitor RF transmitter power output weekly  │
├─────────────────────────────────────────────────┤
│  [📅 Schedule] [📜 History] [📄 Export Report]  │
└─────────────────────────────────────────────────┘
```

### 8.3 Maintenance Status Levels

| Status | Days Until Service | Color | Action Required |
|--------|-------------------|-------|-----------------|
| **Excellent** | 90+ days | 🟢 Green | Monitor status |
| **Good** | 60-90 days | 🟢 Light Green | Plan maintenance |
| **Fair** | 30-60 days | 🟡 Yellow | Schedule soon |
| **Poor** | 7-30 days | 🟠 Orange | Schedule urgently |
| **Service Required** | 1-7 days | 🟠 Red-Orange | Service ASAP |
| **Critical** | 0 days | 🔴 Red | Immediate service |

### 8.4 Monitored Components

#### 8.4.1 RF Equipment
- **Radar Antenna Array**
- **RF Transmitter**
- **RF Receiver**

#### 8.4.2 Mechanical Systems
- **Servo Motor (Azimuth)**
- **Servo Motor (Elevation)**
- **Cooling System**

#### 8.4.3 Power Systems
- **Power Supply Unit**
- **Backup Battery**

#### 8.4.4 Processing Units
- **Signal Processor**
- **Control Computer**

#### 8.4.5 Storage Systems
- **Data Storage Array**

#### 8.4.6 Electrical Systems
- **Network Interface**

### 8.5 Understanding Component Status

Each component displays:

**Condition Percentage (0-100%):**
- Calculated from operating hours and component health
- Higher = better condition

**Days Until Maintenance:**
- Predicted days before service needed
- Based on condition degradation rate

**Operating Hours:**
- Total hours component has operated
- Reset after major maintenance

**Last Maintenance Date:**
- Date of most recent service
- Helps track maintenance intervals

**Category:**
- Component classification (RF, Mechanical, Power, etc.)

### 8.6 Viewing Component Details

**To view detailed component information:**

1. **Click on component** in the list
2. **Detail dialog appears** showing:
   - Component name and category
   - Current condition percentage
   - Days until maintenance
   - Operating hours
   - Last maintenance date
   - Specific recommendations
   - Maintenance history

### 8.7 Maintenance Schedule

The schedule table shows all maintenance due within 60 days:

**Priority Levels:**

| Priority | Description | Color |
|----------|-------------|-------|
| **Critical** | 0-7 days | Red |
| **High** | 8-21 days | Orange |
| **Medium** | 22-45 days | Yellow |
| **Low** | 46-60 days | Green |

**Maintenance Types:**

| Type | Description |
|------|-------------|
| **Emergency** | Immediate unplanned maintenance |
| **Preventive** | Scheduled preventive service |
| **Routine** | Regular maintenance tasks |

### 8.8 Maintenance Recommendations

The system provides AI-style recommendations based on:

- Component condition trends
- Operating hour thresholds
- Historical failure patterns
- Manufacturer guidelines

**Recommendation Priority:**
- **URGENT** - Immediate action required
- **Important** - Schedule soon
- **Routine** - Normal maintenance window

### 8.9 Scheduling Maintenance

**To schedule maintenance:**

1. Click **📅 Schedule** button
2. **Scheduling dialog appears**
3. Select component from dropdown
4. Choose maintenance date
5. Add notes (optional)
6. Click **Save**

ℹ️ **Note:** Scheduled maintenance appears in the calendar.

### 8.10 Viewing Maintenance History

**To view maintenance history:**

1. Click **📜 History** button
2. **History dialog appears** showing:
   - All past maintenance events
   - Date performed
   - Component serviced
   - Technician notes
   - Parts replaced

### 8.11 Exporting Maintenance Reports

**To export maintenance report:**

1. Click **📄 Export Report** button
2. Choose save location
3. Report saved as text file

**Report includes:**
- System condition summary
- All component statuses
- Maintenance schedule
- Recommendations
- Component operating hours
- Timestamp and system info

---

## 9. ANALYTICS & CHARTS

### 9.1 Opening Analytics Widget

**Method 1:** Press `A` key  
**Method 2:** View → Analytics Widget

### 9.2 Analytics Features

The Analytics Widget provides:

- Track count statistics
- Track distribution by identity
- Speed analysis
- Range distribution
- Azimuth coverage

### 9.3 Charts Widget

The Charts Widget displays real-time visualizations:

- Time-series track count
- Speed histograms
- Range/azimuth plots
- Performance metrics

**To show Charts Widget:**
- View → Charts Widget
- Widget appears in bottom dock area

---

## 10. CONFIGURATION

### 10.1 Opening Config Panel

**Method 1:** Press `C` key  
**Method 2:** View → Config Panel

### 10.2 Configuration Options

**Display Settings:**
- Map layer visibility
- Track symbol size
- Color schemes
- Range ring spacing

**Performance Settings:**
- Update rates
- Maximum track count
- Map rendering quality

**Network Settings:**
- UDP port configuration
- Network interface selection

---

## 11. TROUBLESHOOTING

### 11.1 Common Issues

#### Issue: No Tracks Displayed

**Possible Causes:**
- No radar data being received
- Incorrect network configuration
- Tracks outside map view

**Solutions:**
1. Check network connection to radar
2. Verify UDP port 2025 is open
3. Press `H` to reset map view
4. Check simulation is running (if simulating)

#### Issue: Simulation Not Working

**Possible Causes:**
- Configuration error
- UDP socket failure

**Solutions:**
1. Check all configuration values are valid
2. Stop and restart simulation
3. Check firewall allows localhost UDP
4. Review error logs

#### Issue: Recording Failed

**Possible Causes:**
- Insufficient disk space
- Directory permissions
- Disk write error

**Solutions:**
1. Check available disk space
2. Verify ~/RadarRecordings/ directory exists
3. Check file permissions
4. Try different storage location

#### Issue: Replay Not Working

**Possible Causes:**
- Corrupted recording file
- Incompatible file version
- File read error

**Solutions:**
1. Verify file is not corrupted
2. Check file format version
3. Try replaying different recording
4. Re-record session if necessary

#### Issue: Widget Disappeared

**Possible Causes:**
- Widget closed accidentally
- Off-screen position

**Solutions:**
1. Use keyboard shortcut to reopen
2. View menu → Reset Layout
3. Check if widget is minimized/tabbed

### 11.2 Performance Issues

**If IRDS is slow or laggy:**

1. Reduce number of simulated tracks
2. Increase simulation update rate
3. Close unused widgets
4. Reduce map rendering quality
5. Check system CPU/memory usage

### 11.3 Getting Help

**Support Resources:**

1. **Built-in Help:** Help → User Manual
2. **Logs:** Check system logs in ~/.irds/logs/
3. **Support Team:** Contact Zoppler Systems Technical Support

**When reporting issues, provide:**
- IRDS version number
- Operating system and version
- Detailed description of issue
- Steps to reproduce
- Error messages (if any)
- System logs

---

## 12. QUICK REFERENCE

### 12.1 Keyboard Shortcuts

| Key | Function |
|-----|----------|
| H | Map Home |
| T | Track Table |
| C | Config Panel |
| I | Interfaces |
| A | Analytics |
| S | Simulation |
| R | Recording |
| M | Health Monitor |
| P | Predictive Maintenance |

### 12.2 Quick Start Checklist

**Starting IRDS:**
- [ ] Launch application
- [ ] Verify Track Table visible
- [ ] Check map displays correctly
- [ ] Verify network connection (if using live radar)

**Running Simulation:**
- [ ] Press `S` to open Simulation
- [ ] Configure parameters
- [ ] Click Start
- [ ] Verify tracks appear on map

**Recording Session:**
- [ ] Press `R` to open Recording
- [ ] Click Record button
- [ ] Monitor duration
- [ ] Click Stop when done
- [ ] Verify file in library

**Checking System Health:**
- [ ] Press `M` to open Health Monitor
- [ ] Review overall health percentage
- [ ] Check for critical alerts
- [ ] Run diagnostics if needed

**Planning Maintenance:**
- [ ] Press `P` to open Predictive Maintenance
- [ ] Review component statuses
- [ ] Check maintenance schedule
- [ ] Schedule required maintenance

### 12.3 File Locations

| Type | Location |
|------|----------|
| Recordings | `~/RadarRecordings/` |
| Configuration | `~/.irds/config/` |
| Logs | `~/.irds/logs/` |
| Exports | User-selected locations |

### 12.4 Status Colors

| Color | Meaning |
|-------|---------|
| 🟢 Green | Good/Healthy/Friend |
| 🟡 Yellow | Warning/Fair/Unknown |
| 🔴 Red | Critical/Error/Hostile |
| 🔵 Blue | Info/Normal |

---

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                             │
│                          ZOPPLER SYSTEMS                                    │
│                      Integrated Radar Display System                        │
│                                                                             │
│  Document: User Manual                                                      │
│  Version: 1.0.0                                                            │
│  Date: October 13, 2025                                                    │
│  Classification: For Official Use                                           │
│                                                                             │
│  © 2025 Zoppler Systems. All rights reserved.                             │
│  For support, contact: support@zopplersystems.com                          │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

**END OF DOCUMENT**
