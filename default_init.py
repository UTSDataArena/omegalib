# This script is executed when the omegalib python interpreter (orun) starts, 
# before running application scripts.
# It sets up a system menu with several config options for sound, navigation, 
# graphics etc. If you want to change (or remove) the default menu, use the  
# orun/initScript config option to specify a new or an empty script.
# You can also change the orun/appStartFunction config option to change the 
# entry point into this script (by default it is set to _onAppStart)
orun('system/quickCommands.py')

speedLabel = None
mainmnu = None

eyeSep = getDefaultCamera().getEyeSeparation()

# add the current path to the data search paths.
import os
addDataPath(os.getcwd())

def _setCamSpeed(speedLevel):
	global speedLabel
	s = 10 ** (speedLevel - 4)
	speedLabel.setText("Navigation Speed: " + str(s) + "x")
	cc = getDefaultCamera().getController()
	if(cc != None):
		cc.setSpeed(s)
		
def _autonearfar(value):
	if(value):
		queueCommand(":autonearfar on")
	else:
		queueCommand(":autonearfar off")

def _displayWand(value):
	if(value):
		queueCommand("getSceneManager().displayWand(0, 1)")
	else:
		queueCommand("getSceneManager().hideWand(0)")
		
def _setSoundServerVolume( value ):
	newVolume = value - 90
	globalVolumeLabel.setText("Global Volume: " + str(newVolume) )
	soundEnv.setServerVolume(newVolume)
	
def _onAppStart():
	global mainmnu
    # mm = getViewer().getMenuManager()
	mm = MenuManager.createAndInitialize()
	mainmnu = mm.createMenu("Main Menu")

	# If menus are in 2d mode, add a menu open button
    # Disabled, just press middle mouse to enable the system
    # menu anywhere..
	# if(not getBoolSetting('config/ui', 'menu3dEnabled', False)):
		# uim = UiModule.instance()
		# wf = uim.getWidgetFactory()
		# mainButton = wf.createButton('mainButton', uim.getUi())
		# mainButton.setText("Main Menu")
		# mainButton.setUIEventCommand('mainmnu.show()')
		# mainButton.setStyleValue('fill', 'black')
		# mainmnu.getContainer().setPosition(Vector2(5, 25))
	
	mi = mainmnu.addImage(loadImage("omegalib-transparent-white.png"))
	ics = mi.getImage().getSize() * 0.1
	mi.getImage().setSize(ics)
	
	mm.setMainMenu(mainmnu)
	sysmnu = mainmnu.addSubMenu("System")
	mi = sysmnu.addButton("Toggle freefly", ":freefly")
	mi.getButton().setCheckable(True)
	mi = sysmnu.addButton("Reset", ":rc")
	mi = sysmnu.addButton("Auto Near / Far", "_autonearfar(%value%)")
	mi.getButton().setCheckable(True)
	mi = sysmnu.addButton("Display Wand", "_displayWand(%value%)")
	mi.getButton().setCheckable(True)
	global speedLabel
	speedLabel = sysmnu.addLabel("sd")
	_setCamSpeed(4)
	ss = sysmnu.addSlider(10, "_setCamSpeed(%value%)")
	ss.getSlider().setValue(4)
	ss.getWidget().setWidth(200)
	
	if( isSoundEnabled() ):
		global soundEnv
		global serverVolume
		global globalVolumeLabel
			
		soundEnv = getSoundEnvironment()
		serverVolume = soundEnv.getServerVolume();
	
		globalVolumeLabel = sysmnu.addLabel("Global Volume: --")
		
		value = serverVolume + 90
		globalVolumeLabel.setText("Global Volume: " + str(serverVolume))
	
		ss = sysmnu.addSlider(99, "_setSoundServerVolume(%value%)")
		ss.getSlider().setValue(60)
		ss.getWidget().setWidth(200)
		
		ss.getSlider().setValue(value)
		
	global eyeSep
	mi = sysmnu.addButton("Enable Stereo", "_doEyeSep()")
	mi.getButton().setCheckable(True)
	mi.getButton().setChecked(getDefaultCamera().getEyeSeparation() == eyeSep)
	
	mi = sysmnu.addButton("Toggle Console", ":c")
	mi = sysmnu.addButton("List Active Modules", "printModules()")
	mi = sysmnu.addButton("Exit omegalib", "_shutdown()")


shuttingDown = False
fadeOutVal = 0

def _doEyeSep():
	global eyeSep
	if getDefaultCamera().getEyeSeparation() != 0:
		eyeSep = getDefaultCamera().getEyeSeparation()
		getDefaultCamera().setEyeSeparation(0)
	else:
		getDefaultCamera().setEyeSeparation(eyeSep)


def _shutdown():
	global shuttingDown
	global fadeOutVal
	shuttingDown = True
	fadeOutVal = 0

def onUpdate(frame, t, dt):
	global shuttingDown
	global fadeOutVal
	if(shuttingDown):
		if(fadeOutVal >= 1):
			if( isSoundEnabled() ):
				scsound.shutdown()
			oexit()
		else:
			uim = UiModule.instance()
			ui = uim.getUi()
			alpha = int(fadeOutVal * 256)
			ui.setStyleValue('fill', '#000000' + hex(alpha)[2:])
			fadeOutVal += dt
	
setUpdateFunction(onUpdate)
