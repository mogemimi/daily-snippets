// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "somera/Optional.h"
#include <string>

namespace somera {
namespace iTunesNowPlaying {

struct Track {
    std::string trackName;
    std::string artistName;
    std::string albumName;
};

somera::Optional<Track> getCurrentTrack();

} // namespace iTunesNowPlaying
} // namespace somera
