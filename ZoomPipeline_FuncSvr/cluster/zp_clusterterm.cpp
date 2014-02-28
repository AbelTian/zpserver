#include "zp_clusterterm.h"
namespace ZP_Cluster{
zp_ClusterTerm::zp_ClusterTerm(const QString & name,int nTransThreads ,int nWorkingThreads,QObject *parent ) :
    QObject(parent)
  ,m_strTermName(name)
{
    m_pClusterEng = new ZPTaskEngine::zp_pipeline(this);
    m_pClusterEng->addThreads(nWorkingThreads);
    m_pClusterNet = new ZPNetwork::zp_net_ThreadPool(8192,this);
    m_pClusterNet->AddClientTransThreads(nTransThreads);

}
void zp_ClusterTerm::StartListen(const QHostAddress &addr, int nPort)
{
    m_pClusterNet->AddListeningAddress(m_strTermName,addr,nPort,false);

}
bool zp_ClusterTerm::JoinCluster(const QHostAddress &addr, int nPort)
{
    return m_pClusterNet->connectTo(addr,nPort);
}
bool zp_ClusterTerm::canExit()
{
    return m_pClusterEng->canClose() && m_pClusterNet->CanExit();
}
}
