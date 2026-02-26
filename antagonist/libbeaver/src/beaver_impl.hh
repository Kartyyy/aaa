#pragma once

#include "../include/libbeaver/beaver.hh"
#include <string>

namespace beaver
{
    class BeaverImpl : public Beaver
    {
    public:
        BeaverImpl(const std::string& video_path);

        ~BeaverImpl() override = default;

        void display_video() override;

    private:
    	std::string video_path_;
    };
} // namespace beaver
