create (_0:`Object` {`code`:"000013", `name`:"switch", `type`:"sc"})
create (_1:`Object`:`sk` {`id`:"000002", `name`:"LED"})
create (_2:`Object`:`sk` {`id`:"000003", `name`:"Servo"})
create (_7:`Action` {`Status`:"ON", `code`:"000017"})
create (_9:`Action` {`Status`:"ON", `code`:"000016"})
create (_10:`Object` {`code`:"000014", `name`:"led", `protocol`:"TCP", `type`:"sk"})
create (_13:`Device` {`code`:"000012", `ip`:"192.168.65.238", `model`:"UNO", `online`:"true", `type`:"Arduino"})
create (_14:`Device` {`code`:"000011", `ip`:"192.168.65.241", `model`:"UNO", `online`:"true", `type`:"Arduino"})
create (_17:`Device` {`code`:"000020", `ip`:"192.168.65.238", `model`:"UNO", `online`:"true", `type`:"Arduino"})
create (_18:`Object` {`code`:"000021", `name`:"led", `protocol`:"TCP", `type`:"sk"})
create (_19:`Action` {`Status`:"ON", `code`:"000022"})
match(a:Object{code:"000013"}),(b:Object{code:"000021"}) MERGE (a)-[r:LINK]->(b)
match(a:Object{code:"000013"}),(b:Object{code:"000014"}) MERGE (a)-[r:LINK]->(b)
match(a:Device{code:"000020"}),(b:Object{code:"000021"}) MERGE (a)-[r:HAVE]->(b)
match(a:Device{code:"000011"}),(b:Object{code:"000013"}) MERGE (a)-[r:HAVE]->(b)
match(a:Device{code:"000012"}),(b:Object{code:"000014"}) MERGE (a)-[r:HAVE]->(b)
match(a:Object{code:"000014"}),(b:Action{code:"000016"}) MERGE (a)-[r:HAVE]->(b)
match(a:Object{code:"000013"}),(b:Action{code:"000017"}) MERGE (a)-[r:HAVE]->(b)
match(a:Object{code:"000021"}),(b:Action{code:"000022"}) MERGE (a)-[r:HAVE]->(b)

// Como hacerlo 
1. Ejecuta todas las creaciones primero
2. Ejecuta una por una las relaciones. No las mandes todas de Golpe.