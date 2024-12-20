#pragma once
#include "macro-action-edit.hpp"
#include "hotkey-helpers.hpp"
#include "duration-control.hpp"

#include <QComboBox>
#include <QCheckBox>
#include <QHBoxLayout>

namespace advss {

class MacroActionHotkey : public MacroAction {
public:
	MacroActionHotkey(Macro *m) : MacroAction(m) {}
	bool PerformAction();
	void LogAction() const;
	bool Save(obs_data_t *obj) const;
	bool Load(obs_data_t *obj);
	std::string GetId() const { return id; };
	static std::shared_ptr<MacroAction> Create(Macro *m);
	std::shared_ptr<MacroAction> Copy() const;

	enum class Action {
		OBS_HOTKEY,
		CUSTOM,
	};
	Action _action = Action::OBS_HOTKEY;

	obs_hotkey_registerer_type _hotkeyType = OBS_HOTKEY_REGISTERER_FRONTEND;
	std::string _hotkeyName;

	HotkeyType _key = HotkeyType::Key_NoKey;
	bool _leftShift = false;
	bool _rightShift = false;
	bool _leftCtrl = false;
	bool _rightCtrl = false;
	bool _leftAlt = false;
	bool _rightAlt = false;
	bool _leftMeta = false;
	bool _rightMeta = false;
	Duration _duration = 0.3;
#ifdef __APPLE__
	bool _onlySendToObs = true;
#else
	bool _onlySendToObs = false;
#endif

private:
	void SendOBSHotkey();
	void SendCustomHotkey();

	static bool _registered;
	static const std::string id;
};

class MacroActionHotkeyEdit : public QWidget {
	Q_OBJECT

public:
	MacroActionHotkeyEdit(
		QWidget *parent,
		std::shared_ptr<MacroActionHotkey> entryData = nullptr);
	void UpdateEntryData();
	static QWidget *Create(QWidget *parent,
			       std::shared_ptr<MacroAction> action)
	{
		return new MacroActionHotkeyEdit(
			parent,
			std::dynamic_pointer_cast<MacroActionHotkey>(action));
	}

private slots:
	void ActionChanged(int key);
	void HotkeyTypeChanged(int key);
	void OBSHotkeyChanged(int);
	void KeyChanged(int key);
	void LShiftChanged(int state);
	void RShiftChanged(int state);
	void LCtrlChanged(int state);
	void RCtrlChanged(int state);
	void LAltChanged(int state);
	void RAltChanged(int state);
	void LMetaChanged(int state);
	void RMetaChanged(int state);
	void DurationChanged(const Duration &);
	void OnlySendToOBSChanged(int state);

protected:
	QComboBox *_actionType;
	QComboBox *_hotkeyType;
	QComboBox *_obsHotkeys;
	QComboBox *_keys;
	QCheckBox *_leftShift;
	QCheckBox *_rightShift;
	QCheckBox *_leftCtrl;
	QCheckBox *_rightCtrl;
	QCheckBox *_leftAlt;
	QCheckBox *_rightAlt;
	QCheckBox *_leftMeta;
	QCheckBox *_rightMeta;
	DurationSelection *_duration;
	QCheckBox *_onlySendToOBS;
	QLabel *_noKeyPressSimulationWarning;

	std::shared_ptr<MacroActionHotkey> _entryData;

private:
	void RepopulateOBSHotkeySelection();
	void SetWidgetVisibility();

	QHBoxLayout *_entryLayout;
	QHBoxLayout *_keyConfigLayout;
	bool _loading = true;
};

} // namespace advss
