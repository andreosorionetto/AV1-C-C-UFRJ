select Carro_Renavam, Valor, from Clientes
inner join aluga on Clientes.`id Cliente` = aluga.`Clientes_id Cliente`
inner join paga on Clientes.`id Cliente` = paga.`Clientes_id Cliente`
inner join pagamento on Pagamento.`id Pagamento` = paga.`Pagamento_id Pagamento`
where Clientes.`id Cliente` = 21432
order by valor desc