import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtCharts 2.15

Rectangle {
    id: root
    anchors.fill: parent
    color: "#f8fafc" // Light modern background

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        margins: 10

        RowLayout {
            spacing: 10
            Layout.fillWidth: true
            Layout.preferredHeight: 200

//            // Circular Gauge
//            Gauge {
//                id: gauge1
//                value: 68
//                anchors.verticalCenter: parent.verticalCenter
//                style: GaugeStyle {
//                    valueBar: Rectangle { color: "#00ffff" }
//                    background: Rectangle { color: "#111" }
//                }
//            }

            // Line Chart
            ChartView {
                antialiasing: true
                theme: ChartView.ChartThemeLight
                backgroundColor: "#ffffff"
                LineSeries {
                    name: "Signal"
                    color: "#3b82f6"
                   // points: [Qt.point(0,1), Qt.point(1,3), Qt.point(2,1), Qt.point(3,4)]
                }
                axes {
                    ValueAxis { 
                        min: 0; max: 3
                        color: "#334155"
                        labelsColor: "#64748b"
                    }
                    ValueAxis { 
                        min: 0; max: 5
                        color: "#334155"
                        labelsColor: "#64748b"
                    }
                }
            }
        }

        // Radar Placeholder
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#ffffff"
            radius: 12
            border.color: "#3b82f6"
            border.width: 2
            
            // Subtle gradient background
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#ffffff" }
                GradientStop { position: 1.0; color: "#f8fafc" }
            }
            
            Text {
                anchors.centerIn: parent
                text: "🎯 Radar Display Area"
                color: "#334155"
                font.pixelSize: 18
                font.weight: Font.Medium
            }
        }
    }
}
