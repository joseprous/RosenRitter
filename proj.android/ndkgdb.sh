APPNAME="RosenRitter"
APP_ANDROID_NAME="com.teamhaskell.rosenritter"
ANDROID_SDK_ROOT="/opt/android-sdk-update-manager"
NDK_ROOT=""
COCOS2DX_ROOT="/home/jose/programas/cocos2d-x"

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_ROOT="$DIR/.."
APP_ANDROID_ROOT="$COCOS2DX_ROOT/$APPNAME/proj.android"

echo "NDK_ROOT = $NDK_ROOT"
echo "ANDROID_SDK_ROOT = $ANDROID_SDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"
echo "APP_ANDROID_NAME = $APP_ANDROID_NAME"

echo
echo "Killing and restarting ${APP_ANDROID_NAME}"
echo

#set -x
"${ANDROID_SDK_ROOT}"/platform-tools/adb shell am force-stop "${APP_ANDROID_NAME}"

NDK_MODULE_PATH="${COCOS2DX_ROOT}":"${COCOS2DX_ROOT}"/cocos2dx/platform/third_party/android/prebuilt \
        "${NDK_ROOT}"/ndk-gdb \
        --adb="${ANDROID_SDK_ROOT}"/platform-tools/adb \
        --verbose \
        --start \
        --force
