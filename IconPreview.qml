import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: window
    width: 600
    height: 400
    visible: true
    title: "Sophisticated Icon Preview"
    color: "#f3f4f6"
    
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#e5e7eb" }
            GradientStop { position: 1.0; color: "#d1d5db" }
        }
        
        Column {
            anchors.centerIn: parent
            spacing: 30
            
            Text {
                text: "🎯 Sophisticated QML Icons"
                color: "#ffffff"
                font.pixelSize: 24
                font.weight: Font.Bold
                anchors.horizontalCenter: parent.horizontalCenter
            }
            
            // Icon toolbar preview
            Rectangle {
                width: 400
                height: 60
                color: Qt.rgba(243/255, 244/255, 246/255, 0.7)
                radius: 12
                border.width: 1
                border.color: Qt.rgba(107, 114, 128, 0.6)
                
                Row {
                    anchors.centerIn: parent
                    spacing: 12
                    
                    Loader {
                        source: "Icons/IconButton.qml"
                        onLoaded: {
                            item.iconType = "loadmap"
                            item.toolTip = "Load Map"
                        }
                    }
                    
                    Loader {
                        source: "Icons/IconButton.qml"
                        onLoaded: {
                            item.iconType = "disablemap"
                            item.toolTip = "Disable Map"
                            item.isToggled = false
                        }
                    }
                    
                    Loader {
                        source: "Icons/IconButton.qml"
                        onLoaded: {
                            item.iconType = "zoomfit"
                            item.toolTip = "Zoom Fit"
                        }
                    }
                    
                    Loader {
                        source: "Icons/IconButton.qml"
                        onLoaded: {
                            item.iconType = "home"
                            item.toolTip = "Home"
                        }
                    }
                    
                    Loader {
                        source: "Icons/IconButton.qml"
                        onLoaded: {
                            item.iconType = "grid"
                            item.toolTip = "Grid"
                            item.isToggled = true
                        }
                    }
                    
                    Loader {
                        source: "Icons/IconButton.qml"
                        onLoaded: {
                            item.iconType = "compass"
                            item.toolTip = "Compass"
                        }
                    }
                    
                    Loader {
                        source: "Icons/IconButton.qml"
                        onLoaded: {
                            item.iconType = "table"
                            item.toolTip = "Table"
                        }
                    }
                    
                    Loader {
                        source: "Icons/IconButton.qml"
                        onLoaded: {
                            item.iconType = "settings"
                            item.toolTip = "Settings"
                        }
                    }
                }
            }
            
            Text {
                text: "✨ Features:\n• Transparent backgrounds\n• Smooth hover animations\n• Toggle state indicators\n• Ripple click effects\n• Sophisticated vector graphics"
                color: "#6b7280"
                font.pixelSize: 14
                lineHeight: 1.5
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}