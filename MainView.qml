import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtCharts 2.15

Rectangle {
    id: root
    anchors.fill: parent
    color: "#1a1a1a" // Dark grey background

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
                theme: ChartView.ChartThemeDark
                backgroundColor: "#2a2a2a"
                LineSeries {
                    name: "Signal"
                   // points: [Qt.point(0,1), Qt.point(1,3), Qt.point(2,1), Qt.point(3,4)]
                }
                axes {
                    ValueAxis { min: 0; max: 3 }
                    ValueAxis { min: 0; max: 5 }
                }
            }
        }

        // Radar Placeholder
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#2a2a2a"
            radius: 10
            border.color: "#8a8a8a"
            Text {
                anchors.centerIn: parent
                text: "Radar Placeholder"
                color: "#aaaaaa"
            }
        }
    }
}
