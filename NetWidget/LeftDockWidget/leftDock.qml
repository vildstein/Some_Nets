import QtQuick
import QtQuick.Controls
import QtQuick.Window
import AppNetWidget 1.0





Rectangle {
//ApplicationWindow {
	id: root
	visible: true

	width: 500
	height: 500

	// Window {
	// 	id: winn
	// 	visible: true
	// 	width: 50
	// 	height: 50
	// 	color: "red"

	// 	Text {
	// 		id: winText

	// 	}

	// 	Button {
	// 		anchors.centerIn: winn
	// 		visible: true
	// 		width: 20
	// 		height: 20
	// 		text: "Ok"

	// 	}
	// }

	// here we use the Window.active and Window.palette ordinary properties
	//color: active ? palette.active.window : palette.inactive.window

	Text {
		id: redText
		anchors.top: parent.top
		anchors.topMargin: 50
		anchors.horizontalCenter: parent.horizontalCenter

		text: "Hello World!"
		font.family: "Helvetica"
		font.pointSize: 24
		color: "red"
	}

	Button {
		anchors.centerIn: parent
		visible: true
		width: 100
		height: 50
		text: "Ok"

	}

	function fuckOff() {
		console.log("fuckOffFuncton");
	}
}





