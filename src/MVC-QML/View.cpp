// Copyright 2013 Johann Duscher (a.k.a. Jonny Dee). All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
//    1. Redistributions of source code must retain the above copyright notice, this list of
//       conditions and the following disclaimer.
//
//    2. Redistributions in binary form must reproduce the above copyright notice, this list
//       of conditions and the following disclaimer in the documentation and/or other materials
//       provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY JOHANN DUSCHER ''AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
// FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and documentation are those of the
// authors and should not be interpreted as representing official policies, either expressed
// or implied, of Johann Duscher.

#include "Model.hpp"
#include "View.hpp"
#include "IController.hpp"

#include <QDebug>
#include <QQuickItem>


View::View(QWindow *parent)
    : super(parent),
      m_controller(0)
{
    setSource(QUrl("qrc:///qml/View.qml"));

    connect(rootObject(), SIGNAL(textField_textChanged()), SLOT(textField_textChanged()));
    connect(rootObject(), SIGNAL(quitButton_clicked()), SLOT(quitButton_clicked()));
}

void View::setController(IController& value)
{
    m_controller = &value;

    connect(&m_controller->model(), &Model::textChanged, this, &View::on_model_textChanged);
}

void View::show()
{
    setText(m_controller->model().text());
    super::show();
}

QString View::text() const
{
    return rootObject()->property("textField_text").toString();
}

void View::setText(const QString& value)
{
    rootObject()->setProperty("textField_text", value);
}

void View::on_model_textChanged(const QString& value)
{
    qDebug() << Q_FUNC_INFO;
    setText(value);
}

void View::textField_textChanged()
{
    qDebug() << Q_FUNC_INFO;
    m_controller->changeText(text());
}

void View::quitButton_clicked()
{
    qDebug() << Q_FUNC_INFO;
    m_controller->quit();
}
