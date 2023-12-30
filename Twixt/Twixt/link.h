#pragma once

#include "peg.h";
#include<iostream>


class Link {
public:
    Link();
    Link(std::shared_ptr<Peg> pegStart, std::shared_ptr<Peg> pegEnd);
    std::shared_ptr<Peg> GetPegStart() const;
    void SetPegStart(std::shared_ptr<Peg> pegStart);
    std::shared_ptr<Peg> GetPegEnd() const;
    void SetPegEnd(std::shared_ptr<Peg> pegEnd);
private:
    std::shared_ptr<Peg> m_pegStart;
    std::shared_ptr<Peg> m_pegEnd;
};

std::ostream& operator<<(std::ostream& os, const Link& link);