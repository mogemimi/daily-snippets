// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "iTunesNowplaying.h"
#include "somera/SubprocessHelper.h"
#include <sstream>
#include <utility>
#ifdef __APPLE_CC__
#include <Availability.h>
#endif

namespace somera {
namespace iTunesNowPlaying {

somera::Optional<Track> getCurrentTrack()
{
#if defined(__APPLE_CC__) \
    && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_8)
    // for Mac OS X
#define SOMERA_TOSTRING(x) std::string(#x)
    auto output = SubprocessHelper::call("osascript -e" + SOMERA_TOSTRING(
        'try' -e
            'tell application "iTunes"' -e
                'set trackName to name of current track' -e
                'set artistName to artist of current track' -e
                'set albumName to album of current track' -e
                'return trackName & "\n" & artistName & "\n" & albumName' -e
            'end tell' -e
        'end try'
    ));

    if (output.empty()) {
        return somera::NullOpt;
    }

    Track track;
    std::stringstream stream;
    stream << output;
    std::getline(stream, track.trackName, '\n');
    std::getline(stream, track.artistName, '\n');
    std::getline(stream, track.albumName, '\n');
    return std::move(track);
#else
    return somera::NullOpt;
#endif
}

} // namespace iTunesNowPlaying
} // namespace somera
