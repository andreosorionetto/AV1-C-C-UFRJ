select sum(Valor), marca
from `faz parte`
inner join carro on carro.Renavam = `faz parte`.Carro_Renavam
inner join contrato on contrato.`id Contrato` = `faz parte`.`Contrato_id Contrato`
inner join estabelece on estabelece.`Contrato_id Contrato` = contrato.`id Contrato`
inner join pagamento on estabelece.`Pagamento_id Pagamento` = pagamento.`id Pagamento`
where `Inicio` > '2018-01-01'
group by marca
having sum(Valor) > 100.0;
