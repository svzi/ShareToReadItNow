/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.2

NavigationPane {
    
    id: nav
    
    Page {
        titleBar: TitleBar {
            title: qsTr("Share To ReadItNow")
        }
        
        ScrollView {
            Container {
                topPadding: 20
                bottomPadding: 20
                leftPadding: 20
                rightPadding: 20
                
                Label {
                    text: qsTr("Text to Share:")
                }
                TextArea {
                    id: textareaText
                    text: "This string contains links like http://blog.sven-ziegler.com/2015/09/20/pocket-integration-via-readitnow-on-blackberry-10/ and http://devblog.blackberry.com/2015/08/this-week-in-blackberry-world-vendor-stats/ ! Both will be stored to Pocket without any issues. :-)"
                }
                Button {
                    horizontalAlignment: HorizontalAlignment.Fill
                    text: qsTr("Share Text to ReadItNow!")
                    onClicked: {
                        _app.invokeReadItNowWithText(textareaText.text);
                    }
                }
                
                Divider {
                
                }   
                Label {
                    text: qsTr("URL to Share:")
                }
                
                TextArea {
                    id: textareaURL
                    text: "http://blog.sven-ziegler.com/2015/09/20/pocket-integration-via-readitnow-on-blackberry-10/"
                }     
                
                Button {
                    horizontalAlignment: HorizontalAlignment.Fill
                    text: qsTr("Share URL to ReadItNow!")
                    onClicked: {
                        _app.invokeReadItNowWithURL(textareaURL.text);
                    }
                }
            
            }
        }
    }
   
    attachedObjects: [
        ComponentDefinition {
            id: readItNowAdvertise
            source: "AdvertiseReadItNow.qml"
        }
    ]
    
    function showReadItNowAd() {
        var page = readItNowAdvertise.createObject();
        nav.push(page);
    }
    
    onCreationCompleted: {
        _app.readitnowNotFound.connect(showReadItNowAd);
    }
    
}
