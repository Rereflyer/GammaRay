/*
  texturetab.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "texturetab.h"
#include "ui_texturetab.h"
#include <ui/propertywidget.h>

#include <QComboBox>
#include <QToolBar>

using namespace GammaRay;

TextureTab::TextureTab(PropertyWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TextureTab)
{
    ui->setupUi(this);
    ui->textureView->setName(parent->objectBaseName() + QStringLiteral(".texture.remoteView"));

    auto toolbar = new QToolBar;
    toolbar->setIconSize(QSize(16, 16));
    toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    ui->layout->setMenuBar(toolbar);

    foreach (auto action, ui->textureView->interactionModeActions()->actions())
        toolbar->addAction(action);
    toolbar->addSeparator();

    toolbar->addAction(ui->textureView->zoomOutAction());
    auto zoom = new QComboBox;
    zoom->setModel(ui->textureView->zoomLevelModel());
    toolbar->addWidget(zoom);
    toolbar->addAction(ui->textureView->zoomInAction());

    ui->textureView->setSupportedInteractionModes(RemoteViewWidget::ViewInteraction | RemoteViewWidget::Measuring);

    connect(zoom, SIGNAL(currentIndexChanged(int)), ui->textureView, SLOT(setZoomLevel(int)));
    connect(ui->textureView, SIGNAL(zoomLevelChanged(int)), zoom, SLOT(setCurrentIndex(int)));
    zoom->setCurrentIndex(ui->textureView->zoomLevelIndex());
}

TextureTab::~TextureTab()
{
}
