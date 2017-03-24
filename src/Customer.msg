
namespace caiaginillo;

packet Customer {
    simtime_t creationTime;
    simtime_t qct;
    simtime_t ct;
    simtime_t qwt;
    simtime_t wt;
    bool hasToWrap;
    bool checkedOut;
}
