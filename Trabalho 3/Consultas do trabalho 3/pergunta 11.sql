select min(Valor), max(Valor) from Clientes
inner join aluga on Clientes.`id Cliente` = aluga.`Clientes_id Cliente`
inner join paga on Clientes.`id Cliente` = paga.`Clientes_id Cliente`
inner join pagamento on Pagamento.`id Pagamento` = paga.`Pagamento_id Pagamento`
inner join carro on Carro.Renavam = Aluga.Carro_Renavam
inner join `é contraparte` on `é contraparte`.`Clientes_id Cliente` = Clientes.`id Cliente`
inner join contrato on Contrato.`id Contrato` = `é contraparte`.`Contrato_id Contrato`
where `id Cliente` = 21432 and Inicio > '2018-07-01' and Inicio < '2019-01-01'
group by Marca