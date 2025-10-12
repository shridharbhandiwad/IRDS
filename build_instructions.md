# Radar Display System - Build Instructions

## Prerequisites

This project requires Qt5 development environment with the following components:
- Qt5 Core, Widgets, Network, Quick, QuickWidgets, QuickControls2, Charts
- QGIS development libraries (qgis-dev)
- C++11 compiler (gcc/g++)

### Ubuntu/Debian Installation:
```bash
sudo apt-get update
sudo apt-get install qt5-default qtbase5-dev qtdeclarative5-dev qtquickcontrols2-5-dev
sudo apt-get install libqt5charts5-dev libqt5quickwidgets5
sudo apt-get install qgis-dev libqgis-dev
sudo apt-get install build-essential
```

## Build Process

1. **Generate Makefile:**
   ```bash
   qmake RadarDisplay.pro
   ```

2. **Compile the project:**
   ```bash
   make -j$(nproc)
   ```

3. **Run the application:**
   ```bash
   ./bin/RadarDisplay
   ```

## Project Structure

### New Features Added:

#### 1. Simulation Control Widget (`MapDisplay/csimulationwidget.*`)
- **Purpose**: Generate simulated radar tracks for testing
- **Features**:
  - Real-time UDP track generation within 10km range
  - Multiple azimuth angles and realistic movement patterns
  - Configurable track count, range, and update rates
  - Pre-defined scenarios (Air Defense, Naval Patrol, etc.)
  - Real-time track position updates with collision avoidance

#### 2. Screen Recording Widget (`MapDisplay/cscreenrecorderwidget.*`)
- **Purpose**: Record and replay radar display sessions
- **Features**:
  - Full screen recording with configurable quality and frame rate
  - Screenshot capture functionality
  - Recording session management and playback
  - Export recordings to standard formats
  - Disk space monitoring

#### 3. Health Monitoring Widget (`MapDisplay/chealthmonitorwidget.*`)
- **Purpose**: Monitor system health and component status
- **Features**:
  - Real-time monitoring of hardware/software components
  - Rich status indicators with color-coded health levels
  - Component categorization (Hardware, Software, Network, Storage, Sensors)
  - Automated alerts and health degradation detection
  - Detailed component information and history tracking

#### 4. Predictive Maintenance Widget (`MapDisplay/cpredictivemaintenancewidget.*`)
- **Purpose**: Predictive maintenance scheduling and management
- **Features**:
  - AI-driven maintenance predictions based on component wear
  - Maintenance calendar with scheduled tasks
  - Priority-based maintenance alerts
  - Component reliability tracking and wear level monitoring
  - Maintenance history and reporting

### Enhanced User Interface:

#### Keyboard Shortcuts:
- **T**: Toggle track table visibility
- **C**: Toggle control panel visibility
- **I**: Toggle interfaces panel visibility
- **S**: Toggle simulation widget visibility
- **R**: Toggle screen recorder widget visibility
- **M**: Toggle health monitor widget visibility
- **P**: Toggle predictive maintenance widget visibility
- **H**: Map home view
- **A**: Toggle analytics panel visibility

#### Layout Improvements:
- **Track table**: Now visible on startup (analytics moved to tab)
- **Charts**: Optimized horizontal sizing for better screen utilization
- **Dockable panels**: All widgets are dockable, resizable, and can be floated
- **Modern theme**: Consistent dark theme across all components

### Technical Implementation:

#### Simulation Engine:
- UDP socket communication on port 12345
- Real-time track generation with physics-based movement
- Configurable scenarios with different track behaviors
- Support for different track identities (Friend, Hostile, Unknown)

#### Recording System:
- Frame-based recording with metadata storage
- JSON-based session management
- Configurable quality settings (50%-100%)
- Variable frame rates (1-60 FPS)

#### Health Monitoring:
- Component-based architecture with extensible health metrics
- Real-time data simulation with realistic degradation patterns
- Alert system with severity levels and automatic notifications
- Export functionality for health reports

#### Predictive Maintenance:
- Machine learning-inspired algorithms for wear prediction
- Calendar integration for maintenance scheduling
- Component lifecycle tracking with operating hours
- Maintenance completion workflow with status updates

## Usage Guide

### Starting a Simulation:
1. Press **S** to open the Simulation widget
2. Configure track count and range parameters
3. Select a scenario from the dropdown
4. Click "Generate Tracks" to create initial tracks
5. Click "Start" to begin real-time simulation
6. Tracks will appear on the radar display and in the track table

### Recording a Session:
1. Press **R** to open the Screen Recorder widget
2. Adjust quality and frame rate settings
3. Click "Record" to start recording
4. Perform radar operations as needed
5. Click "Stop" to end recording
6. Use "Play" to replay recorded sessions

### Monitoring System Health:
1. Press **M** to open the Health Monitor widget
2. View overall system status and component health
3. Select individual components for detailed information
4. Monitor alerts in the alerts panel
5. Export health reports as needed

### Managing Maintenance:
1. Press **P** to open the Predictive Maintenance widget
2. Review maintenance schedule and priorities
3. Use filters to focus on specific components or statuses
4. Schedule or complete maintenance tasks
5. View maintenance calendar for planning

## Dependencies

- **Qt5**: Core framework for UI and networking
- **QGIS**: Geospatial mapping and coordinate systems
- **C++11**: Modern C++ features for robust implementation

## Notes

- The simulation generates realistic radar tracks with physics-based movement
- All widgets support modern docking and floating capabilities
- The system is designed for 24/7 operation with robust error handling
- Health monitoring provides early warning of potential system issues
- Predictive maintenance helps prevent unexpected downtime