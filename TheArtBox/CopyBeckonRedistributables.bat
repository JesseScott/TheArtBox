ECHO copying Beckon SDK re-distributables from %1

ECHO Copying SDK components
@ECHO OFF
copy %1\Foundation.dll
copy %1\Shadow.dll
copy %1\BodyMotion.dll
copy %1\Gesture.dll
copy %1\FBXReader.dll
copy %1\Vision.dll
copy %1\Platform.dll
copy %1\XORClassifier.dll
copy %1\cv100.dll
copy %1\cxcore100.dll
copy %1\highgui100.dll
copy %1\log4cxx.dll

ECHO Copying SDK interfaces
@ECHO OFF
copy %1\ShadowWrapper.dll
copy %1\ShadowDotNetWrapper.dll
copy %1\OmekBeckonFlash.exe
copy %1\AxInterop.ShockwaveFlashObjects.dll
copy %1\Interop.ShockwaveFlashObjects.dll
copy %1\f_in_box__lib.dll
copy %1\f_in_box.dll

ECHO Copying sensor plug-ins
@ECHO OFF
copy %1\PanasonicInput.dll
copy %1\libmmd.dll
copy %1\Dimagerdll.dll

ECHO Copying gesture packs
@ECHO OFF
xcopy %1\Classifiers Classifiers /e /c /i