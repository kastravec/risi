/***************************************************************************
 *   Copyright (C) 2007 by Petref Saraci                                   *
 *   psaraci@gmail.com                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "initDialog.h"
#include "lineedit.h"

#include <QSettings>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QGroupBox>
#include <QSpinBox>

/**
 * \brief
 * @param parent QWidget
 */
InitDialog::InitDialog( QWidget *parent )
    :QDialog( parent )
{
    setupUI();
    setupConnections();
    setFixedSize( sizeHint() );
}

/**
 * \brief
 */
void InitDialog::setupUI()
{
    //settings are read so default stored values will be used
    QSettings settings;
    settings.beginGroup( "General" );//read the general group first

    //initializing some of the UI controls
    okButton = new QPushButton( tr("Ok"), this );
    cancelButton = new QPushButton( tr("Cancel"), this );
    nickNameLineEdit = new LineEdit( this );
    nickNameLineEdit->setText( settings.value( "nickname", "").toString() );
    advancedOptionsButton = new QRadioButton( tr("Advanced options"), this );
    advancedOptionsButton->setChecked( false );

    settings.endGroup();
    settings.beginGroup( "Server" );

    portSpinBox = new QSpinBox( this );
    portSpinBox->setRange( 1500, 9999 );
    portSpinBox->setValue( settings.value( "port", 2222 ).toInt() );

    advancedOptionsWidget = new QGroupBox( tr("Advanced options:"), this );
    advancedOptionsWidget->setVisible( advancedOptionsButton->isChecked() );
    QHBoxLayout *hl = new QHBoxLayout;
    hl->addWidget( new QLabel( tr("Server port:"), this ) );
    hl->addWidget( portSpinBox );
    advancedOptionsWidget->setLayout( hl );

    QGroupBox *generalGroupBox = new QGroupBox( tr("General: "), this );
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget( new QLabel("Nickname: ") );
    hlayout->addWidget( nickNameLineEdit );
    generalGroupBox->setLayout( hlayout );

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget( okButton );
    hlayout2->addWidget( cancelButton );

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget( generalGroupBox );
    vlayout->addWidget( advancedOptionsButton );
    vlayout->addWidget( advancedOptionsWidget );
    vlayout->addLayout( hlayout2 );

    settings.endGroup();
    setLayout( vlayout );
}

void InitDialog::writeSettings()
{
    QSettings settings;

    settings.beginGroup( "General" );
    settings.setValue( "nickname", nickNameLineEdit->text() );
    settings.endGroup();

    settings.beginGroup( "Server" );
    settings.setValue( "port", portSpinBox->value() );
    settings.endGroup();
}

/**
 * \brief
 */
void InitDialog::setupConnections()
{
    connect( okButton, SIGNAL(pressed()), this, SLOT(okButtonPressed()) );
    connect( cancelButton, SIGNAL(pressed()), this, SLOT(reject()) );
    connect( advancedOptionsButton, SIGNAL(toggled( bool )), this, SLOT(advancedOptionsTriggered()) );
}

/**
 * \brief
 */
void InitDialog::okButtonPressed()//TODO add docs
{
    if( !nickNameLineEdit->text().isEmpty() && portSpinBox->value() != 0)
    {
        writeSettings();
        accept();
    }
    else
        QMessageBox::warning( this, tr(" Warning: "), tr(" The nickname and the server port ( advanced options) cannot be empty !! ") );
}

/**
 * \brief
 */
void InitDialog::advancedOptionsTriggered()//TODO add docs
{
    advancedOptionsWidget->setVisible( advancedOptionsButton->isChecked() );
    setFixedSize( sizeHint() );
}

/**
 * \brief
 * @return QString
 */
const QString InitDialog::nickName() const //TODO add docs
{
    return nickNameLineEdit->text();
}

/**
 * \brief
 * @return int
 */
const int InitDialog::serverPort() const //TODO add docs
{
    return portSpinBox->value();
}


