//
// Generated file, do not edit! Created by opp_msgtool 6.0 from tictoc15.msg.
//

#ifndef __TICTOC15_M_H
#define __TICTOC15_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class TicTocMsg15;
/**
 * Class generated from <tt>tictoc15.msg:2</tt> by opp_msgtool.
 * <pre>
 * message TicTocMsg15
 * {
 *     int source;
 *     int destination;
 *     int hopCount = 0;
 * }
 * </pre>
 */
class TicTocMsg15 : public ::omnetpp::cMessage
{
  protected:
    int source = 0;
    int destination = 0;
    int hopCount = 0;

  private:
    void copy(const TicTocMsg15& other);

  protected:
    bool operator==(const TicTocMsg15&) = delete;

  public:
    TicTocMsg15(const char *name=nullptr, short kind=0);
    TicTocMsg15(const TicTocMsg15& other);
    virtual ~TicTocMsg15();
    TicTocMsg15& operator=(const TicTocMsg15& other);
    virtual TicTocMsg15 *dup() const override {return new TicTocMsg15(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getSource() const;
    virtual void setSource(int source);

    virtual int getDestination() const;
    virtual void setDestination(int destination);

    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TicTocMsg15& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TicTocMsg15& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline TicTocMsg15 *fromAnyPtr(any_ptr ptr) { return check_and_cast<TicTocMsg15*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __TICTOC15_M_H

