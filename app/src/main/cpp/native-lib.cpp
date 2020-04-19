#include <jni.h>
#include <string>
#include <functional>
#include <utils/file.h>
#include "android-base/strings.h"
#include "dex/dex_file.h"
#include "dex/dex_file_loader.h"


extern "C" JNIEXPORT jstring JNICALL
Java_com_lkchan_dexfile_MainActivity_getApkdexInfo(
        JNIEnv *env,
        jobject /* this */, jstring path) {
    const char *str = env->GetStringUTFChars(path, NULL);
    std::string location = str;
    std::string error;

    const bool kVerifyChecksum = true;
    const bool kVerify = true;
    std::string content;
    if (!android_lkchan::base::ReadFileToString(location, &content)) {
        return NULL;
    }
    const art_lkchan::DexFileLoader dex_file_loader;
    std::string error_msg;
    std::vector<std::unique_ptr<const art_lkchan::DexFile>> dex_files;
    if (!dex_file_loader.OpenAll(reinterpret_cast<const uint8_t *>(content.data()),
                                 content.size(),
                                 location,
                                 kVerify,
                                 kVerifyChecksum,
                                 &error_msg,
                                 &dex_files)) {
        // Display returned error message to user. Note that this error behavior
        // differs from the error messages shown by the original Dalvik dexdump.
        return env->NewStringUTF("error ");
    }

    char r[100];
    sprintf(r, " dex file count = %d dex version=%d", dex_files.size(),
            dex_files.size() > 0 ? dex_files[0].get()->GetDexVersion() : 0);
    return env->NewStringUTF(r);
}

