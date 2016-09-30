import QtQuick 2.1
import QtQuick.Controls 1.3
import QtLocation 5.6
import QtPositioning 5.6


//silk board lat 12.917352466802262  long 77.62281109101559
//CMRIT bus stop lat 12.9677261  long 77.71430729999997



    Rectangle{

        property variant lat: latitud
        property double lon: 77.62281109101559

        anchors.fill: parent
        color: "gray"
        id: rect
        Plugin {
            id: mapPlugin
            preferred: "osm"

            // code here to choose the plugin as necessary
        }

        function updateCenter(lat_, lon_){

            //map.pan(lat_,lat_)
            map.center = QtPositioning.coordinate(lat_, lon_)
            //map.latitude = lat_
            map.update()
        }
        function moveCircle(lat_, lon_){
            mapcircle.setGeometry(lat_, lon_)
            mapcircle.update()
        }

        function addCoord(lat_, lon_){
            mappoly.addCoord(QtPositioning.coordinate(lat_,lon_))
            mappoly.update()
        }



        Map {
            id: map
            width: parent.width
            height: parent.height
            plugin: mapPlugin

            center {
                latitude: lat
                longitude: lon
            }

            MapPolyline{
                line.width: 2
                line.color: 'red'
                smooth: true
                id:mappoly
                path: [
                            { latitude: lat, longitude: lon }
                        ]

                function addCoord(coord){
                    addCoordinate(coord)
                    update()
                }
            }

            MapCircle {

                color: "#000000"
                border.color: "#190a33"
                border.width: 4
                smooth: true
                opacity: 1
                id: mapcircle
                radius: 30.0
                center {
                    latitude: lat
                    longitude: lon
                }
                function setGeometry(lat_, lon_){
                    //map.addMapItem(mapcircle)
                    center.latitude = lat_
                    center.longitude = lon_
                    radius = 30
                }
            }

        }


    }



