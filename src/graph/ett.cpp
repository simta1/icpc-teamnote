// root->v path add / node v qry
// upd(in[v], out[v], add) / qry(in[v], out[v])
// node v add / root->v path qry
// upd(in[v], out[v], add]) / qry(in[v])
// 루트가 r로 바뀌었을 때 v의 subtree
// v == r : 전체 트리
// v가 r의 조상이 아님 : 기존 subtree(v) = [tin[v], tout[v]]
// v가 r의 조상임 : 전체에서, v 아래에서 r로 가는 child의 subtree를 뺀 것
