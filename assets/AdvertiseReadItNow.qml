import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        title: qsTr("ReadItNow! not found")
    }
    ScrollView {
        Container {
            leftPadding: 10
            rightPadding: 10
            topPadding: 10
 
            Label {
                text: qsTr("This app supports 'ReadItNow!' for adding stuff to your Pocket account.")
                multiline: true
            }
            Divider {

            }
            Container {
                rightPadding: 10
                leftPadding: 10
                topPadding: 20
                //bottomPadding: 20
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    }
                    Container {
                        verticalAlignment: VerticalAlignment.Top
                        ImageView {
                            verticalAlignment: VerticalAlignment.Center
                            imageSource: "asset:///images/read-it-now-B10-480.png"
                            preferredHeight: 190
                            preferredWidth: 190
                            maxWidth: preferredWidth
                            maxHeight: preferredHeight
                            minHeight: preferredHeight
                            minWidth: preferredWidth
                            scalingMethod: ScalingMethod.AspectFit
                        }
                    }
                    Container {
                        verticalAlignment: VerticalAlignment.Top
                        Label {
                            text: qsTr("No time for surfing? You would like to read everything later, even offline? The solution is ReadItNow! With ReadItNow! you have all saved content neatly arranged for later reading on your BlackBerry® PlayBook™ and BlackBerry® 10 device.")
                            multiline: true
                        }
                        //topPadding: 10
                        rightPadding: 10
                        leftPadding: 20
                        Container {
                             preferredHeight: 30
                        }
                    }
                }
            }
            Divider {

            }
            Label {
                text: qsTr("This app is unable to find 'ReadItNow!' installed on your device. For that reason it's not possible to store any articles to read them later.")
                multiline: true
            }
            Container {
                horizontalAlignment: HorizontalAlignment.Center
                topPadding: 40
                bottomPadding: 40
                Button {
                    horizontalAlignment: HorizontalAlignment.Center
                    text: qsTr("View ReadItNow!")
                    attachedObjects: [
                        Invocation {
                            id: invoke
                            query: InvokeQuery {
                                mimeType: "application/x-bb-appworld"
                                uri: "appworld://content/103642"
                            }
                        }
                    ]
                    onClicked: {
                        invoke.trigger("bb.action.OPEN")
                    }
                }
            }
            Container {
                minHeight: 40
            }
        }
    }
}
