#pragma once

#include <iostream>

class StateSaver
{
public:
    //! constructor should save all flags and precision
    StateSaver(std::ostream& os);
    //! destructor should restore all flags and precision
    ~StateSaver();

private:
    //! original stream
    std::ostream& saved_stream_;
    //! flags of the original stream
    std::ios_base::fmtflags saved_flags_;
    //! precision of the original stream
    std::streamsize saved_precision_;
};
