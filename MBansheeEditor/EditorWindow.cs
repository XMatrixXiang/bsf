﻿using System;
using System.Runtime.CompilerServices;
using BansheeEngine;

namespace BansheeEditor
{
    public class EditorWindow : ScriptObject
    {
        protected EditorGUI GUI;

        public static EditorWindow OpenWindow<T>() where T : EditorWindow
        {
            return Internal_CreateOrGetInstance(typeof(T).Namespace, typeof(T).Name);
        }

        public EditorWindow()
        {
            Internal_CreateInstance(this);
            GUI = new EditorGUI(this);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern EditorWindow Internal_CreateOrGetInstance(string ns, string typeName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_CreateInstance(EditorWindow instance);
    }
}
