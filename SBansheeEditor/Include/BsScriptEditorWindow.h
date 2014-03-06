#pragma once

#include "BsScriptEditorPrerequisites.h"
#include "BsScriptObject.h"

namespace BansheeEditor
{
	class BS_SCR_BED_EXPORT ScriptEditorWindow : public BansheeEngine::ScriptObject<ScriptEditorWindow>
	{
	public:
		static void initMetaData();

		EditorWidgetBase* getEditorWidget() const { return mWidget; }

	private:
		ScriptEditorWindow(const CM::String& windowName);
		~ScriptEditorWindow();

		static MonoObject* internal_createOrGetInstance(MonoString* ns, MonoString* typeName);
		static void internal_createInstance(MonoObject* instance);
		static void internal_destroyInstance(ScriptEditorWindow* nativeInstance);

		static void initRuntimeData();

		static CM::UnorderedMap<CM::String, ScriptEditorWindow*>::type OpenScriptEditorWindows;

		EditorWidgetBase* mWidget;
	};
}