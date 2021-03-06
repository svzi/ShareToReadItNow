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

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeQueryTargetsRequest>
#include <bb/system/InvokeQueryTargetsReply>

using namespace bb::cascades;
using namespace bb::system;

ApplicationUI::ApplicationUI() :
        QObject(), m_readitnowAvailable(false)
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(Application::instance(), SIGNAL(fullscreen()), this, SLOT(check3rdPartyApps()));
    // This is only available in Debug builds
    Q_ASSERT(res);

    res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);

    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // make this class accessable from QML via _app property
    qml->setContextProperty("_app", this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    Application::instance()->setScene(root);

    check3rdPartyApps();
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("ShareToReadItNow_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

void ApplicationUI::check3rdPartyApps()
{
    qDebug() << "check3rdPartyApps()";
    m_readitnowAvailable = false;

    InvokeManager *invokeManager = new InvokeManager(this);
    InvokeQueryTargetsRequest request;
    request.setMimeType("text/plain");
    const InvokeReply *reply = invokeManager->queryTargets(request);
    // Listen for the results
    bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onCheck3rdPartyAppsResponse()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}

void ApplicationUI::onCheck3rdPartyAppsResponse()
{
    qDebug() << "onCheck3rdPartyAppsResponse()";

    // Get the reply from the sender object
    InvokeQueryTargetsReply *reply = qobject_cast<InvokeQueryTargetsReply*>(sender());
    if (reply) {
        if (reply->error() == InvokeReplyError::None) {
            QList<InvokeAction> targetsByAction = reply->actions();
            foreach (const InvokeAction &action, reply->actions()) {
                foreach (const InvokeTarget &target, action.targets()) {
                    //qDebug() << target.name();
                    if (target.name().indexOf("com.svzi.rin") != -1) {
                        m_readitnowAvailable = true;
                    }
                }
            }
        } else if (reply->error() != InvokeReplyError::None) {
            qDebug() << "ERROR:" << reply->error();
        }

        // Clean up the results
        reply->deleteLater();
    }
    qDebug() << "m_readitnowAvailable:" << m_readitnowAvailable;
}

void ApplicationUI::invokeReadItNowWithURL(const QString &url)
{
    if (m_readitnowAvailable) {
        InvokeManager *invokeManager = new InvokeManager(this);
        InvokeRequest request;

        request.setTarget("com.svzi.rin");
        request.setAction("bb.action.SHARE");
        request.setUri(url);

        invokeManager->invoke(request);
    } else {
        emit readitnowNotFound();
    }

}

void ApplicationUI::invokeReadItNowWithText(const QString &text)
{
    if (m_readitnowAvailable) {
        InvokeManager *invokeManager = new InvokeManager(this);
        bb::system::InvokeRequest request;

        request.setTarget("com.svzi.rin");
        request.setAction("bb.action.SHARE");
        request.setData(text.toUtf8());

        invokeManager->invoke(request);
    } else {
        emit readitnowNotFound();
    }

}
