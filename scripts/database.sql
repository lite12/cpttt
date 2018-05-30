CREATE DATABASE  IF NOT EXISTS `record_db` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `record_db`;
-- MySQL dump 10.13  Distrib 5.7.17, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: record_db
-- ------------------------------------------------------
-- Server version	5.7.19-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `user_records`
--

DROP TABLE IF EXISTS `user_records`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_records` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_key` varchar(10) NOT NULL,
  `rec_type` varchar(10) NOT NULL,
  `value` int(11) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=35 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_records`
--

LOCK TABLES `user_records` WRITE;
/*!40000 ALTER TABLE `user_records` DISABLE KEYS */;
INSERT INTO `user_records` VALUES (1,'key','cpu',1),(2,'cpu','11',1),(3,'mem','82',1),(4,'process','243',1),(5,'cpu','2',1),(6,'mem','82',1),(7,'process','243',1),(8,'cpu','3',1),(9,'mem','82',1),(10,'process','242',1),(11,'cpu','2',1),(12,'mem','82',1),(13,'process','242',1),(14,'cpu','2',1),(15,'mem','82',1),(16,'process','242',1),(17,'cpu','2',1),(18,'mem','82',1),(19,'process','242',1),(20,'cpu','9',1),(21,'mem','82',1),(22,'process','242',1),(23,'cpu','2',1),(24,'mem','82',1),(25,'process','242',1),(26,'cpu','1',1),(27,'mem','82',1),(28,'process','242',1),(29,'cpu','2',1),(30,'mem','82',1),(31,'process','242',1),(32,'cpu','1',1),(33,'mem','82',1),(34,'process','242',1);
/*!40000 ALTER TABLE `user_records` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-09-26  4:16:53
