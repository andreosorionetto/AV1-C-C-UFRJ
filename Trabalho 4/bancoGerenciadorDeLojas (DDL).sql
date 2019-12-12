-- MySQL Workbench Forward Engineering

--          PROJETO 3 TMAB
-- Andre Osorio Magaldi Netto                118041914
-- Joao Paulo Alves Loureiro Da Silva        117196504
-- Rodrigo Bagdadi Benoliel                  118031529



SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema esquemagerenciadordelojas
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema esquemagerenciadordelojas
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `esquemagerenciadordelojas` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci ;
USE `esquemagerenciadordelojas` ;

-- -----------------------------------------------------
-- Table `esquemagerenciadordelojas`.`clientes`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `esquemagerenciadordelojas`.`clientes` (
  `idClientes` INT(11) NOT NULL,
  `email` VARCHAR(45) NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `genero` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idClientes`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `esquemagerenciadordelojas`.`lojas`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `esquemagerenciadordelojas`.`lojas` (
  `idLojas` INT(11) NOT NULL,
  `categoria` VARCHAR(45) NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `endereço` VARCHAR(45) NULL DEFAULT NULL,
  `telefone` DOUBLE NULL DEFAULT NULL,
  `x` INT(11) NOT NULL,
  `y` INT(11) NOT NULL,
  PRIMARY KEY (`idLojas`),
  UNIQUE INDEX `idLojas_UNIQUE` (`idLojas` ASC) VISIBLE,
  UNIQUE INDEX `endereço_UNIQUE` (`endereço` ASC) VISIBLE,
  UNIQUE INDEX `telefone_UNIQUE` (`telefone` ASC) VISIBLE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `esquemagerenciadordelojas`.`produtos`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `esquemagerenciadordelojas`.`produtos` (
  `idProdutos` INT(11) NOT NULL,
  `descrição` VARCHAR(45) NULL DEFAULT NULL,
  `nome` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idProdutos`),
  UNIQUE INDEX `idProdutos_UNIQUE` (`idProdutos` ASC) VISIBLE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `esquemagerenciadordelojas`.`compra`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `esquemagerenciadordelojas`.`compra` (
  `Produtos_idProdutos` INT(11) NOT NULL,
  `Lojas_idLojas` INT(11) NOT NULL,
  `Clientes_idClientes` INT(11) NOT NULL,
  `quantidade` INT(11) NULL DEFAULT NULL,
  `dia` DATETIME NOT NULL,
  PRIMARY KEY (`Produtos_idProdutos`, `Lojas_idLojas`, `Clientes_idClientes`, `dia`),
  INDEX `fk_Compra_Lojas1_idx` (`Lojas_idLojas` ASC) VISIBLE,
  INDEX `fk_Compra_Clientes1_idx` (`Clientes_idClientes` ASC) VISIBLE,
  CONSTRAINT `fk_Compra_Clientes1`
    FOREIGN KEY (`Clientes_idClientes`)
    REFERENCES `esquemagerenciadordelojas`.`clientes` (`idClientes`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Compra_Lojas1`
    FOREIGN KEY (`Lojas_idLojas`)
    REFERENCES `esquemagerenciadordelojas`.`lojas` (`idLojas`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Compra_Produtos`
    FOREIGN KEY (`Produtos_idProdutos`)
    REFERENCES `esquemagerenciadordelojas`.`produtos` (`idProdutos`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `esquemagerenciadordelojas`.`possui`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `esquemagerenciadordelojas`.`possui` (
  `Produtos_idProdutos` INT(11) NOT NULL,
  `Lojas_idLojas` INT(11) NOT NULL,
  `quantidade` INT(11) NULL DEFAULT NULL,
  `preço` FLOAT NULL DEFAULT NULL,
  PRIMARY KEY (`Produtos_idProdutos`, `Lojas_idLojas`),
  INDEX `fk_Possui_Lojas1_idx` (`Lojas_idLojas` ASC) VISIBLE,
  CONSTRAINT `fk_Possui_Lojas1`
    FOREIGN KEY (`Lojas_idLojas`)
    REFERENCES `esquemagerenciadordelojas`.`lojas` (`idLojas`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Possui_Produtos1`
    FOREIGN KEY (`Produtos_idProdutos`)
    REFERENCES `esquemagerenciadordelojas`.`produtos` (`idProdutos`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
