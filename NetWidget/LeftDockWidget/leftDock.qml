import QtQuick
import QtQuick.Controls
import AppNetWidget 1.0

Rectangle {

	id: root
	visible: true

	width: 500
	height: 500

	signal appCloseSignal();

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
		text: qsTr("Close App")

		onClicked: {
			root.appCloseSignal();
		}
	}

	onAppCloseSignal: {
		writeMessageIntoConsole("app is about to close");
	}

	function writeMessageIntoConsole(mesg : string ) {
		console.log(mesg);
	}

	function someFunc() {
		console.log("function works");
	}
}





