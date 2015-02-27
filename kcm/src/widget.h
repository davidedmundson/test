/*
 * Copyright (C) 2013  Daniel Vrátil <dvratil@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVariantMap>

#include <kscreen/config.h>

class ProfilesModel;
class QMLOutput;
class QMLScreen;
class ControlPanel;

class QPushButton;
class QComboBox;

class QQuickView;

namespace KScreen
{
class ConfigOperation;
}

class Widget : public QWidget
{
    Q_OBJECT

  public:
    explicit Widget(QWidget *parent = 0);
    virtual ~Widget();

    void setConfig(const KScreen::ConfigPtr &config);
    KScreen::ConfigPtr currentConfig() const;

    void saveScaleRatio();

  protected:
    virtual bool eventFilter(QObject *object, QEvent *event);

  Q_SIGNALS:
    void changed();

  private Q_SLOTS:
    void slotFocusedOutputChanged(QMLOutput *output);

    void slotPrimaryChanged(int index);
    void slotOutputPrimaryChanged();
    void slotOutputConnectedChanged();
    void slotOutputEnabledChanged();

    void slotUnifyOutputs();
    void slotProfileChanged(int index);

    void slotProfilesAboutToUpdate();
    void slotProfilesUpdated();

    void slotIdentifyButtonClicked();
    void slotIdentifyOutputs(KScreen::ConfigOperation *op);
    void clearOutputIdentifiers();

  private:
    void loadQml();
    void initPrimaryCombo();

    KScreen::OutputPtr findOutput(const KScreen::ConfigPtr &config, const QVariantMap &info);

  private:
    QMLScreen *mScreen;
    KScreen::ConfigPtr mConfig;
    KScreen::ConfigPtr mPrevConfig;

    QQuickView *m_declarativeView;
    ControlPanel *m_controlPanel;

    ProfilesModel *mProfilesModel;
    QComboBox *mPrimaryCombo;
    QComboBox *mProfilesCombo;
    QComboBox *mScaleCombo;

    QPushButton *mUnifyButton;
    QPushButton *mSaveProfileButton;

    QList<QQuickView*> mOutputIdentifiers;
    QTimer *mOutputTimer;

};

#endif // WIDGET_H
