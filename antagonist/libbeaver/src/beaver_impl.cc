#include <memory>
#include "beaver_impl.hh"
#include "../externals/libplayer/video_player.hh"
namespace beaver
{
    BeaverImpl::BeaverImpl(const std::string& video_path)
    : video_path_(video_path)
    {}

    void BeaverImpl::display_video()
    {
    	play_video(video_path_);
    }

} // namespace beaver
