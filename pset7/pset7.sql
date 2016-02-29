-- MySQL dump 10.13  Distrib 5.5.46, for debian-linux-gnu (x86_64)
--
-- Host: 0.0.0.0    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.46-0ubuntu0.14.04.2

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
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `transaction` varchar(4) NOT NULL,
  `datetime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `symbol` varchar(6) NOT NULL,
  `shares` int(65) unsigned NOT NULL,
  `price` decimal(65,4) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (2,9,'BUY','2016-02-28 20:28:00','M',2,43.4300),(3,9,'BUY','2016-02-28 20:35:58','TSLA',3,190.3400),(4,9,'BUY','2016-02-28 20:37:42','TSLA',5,190.3400),(5,9,'BUY','2016-02-28 20:44:13','D',3,70.0200),(6,9,'SELL','2016-02-28 20:54:50','F',3,12.4700),(7,9,'SELL','2016-02-28 20:56:41','YHOO',1,31.3700),(8,9,'BUY','2016-02-28 20:56:57','TSLA',23,190.3400),(9,11,'BUY','2016-02-29 02:01:36','M',32,43.4300),(10,23,'BUY','2016-02-29 04:21:58','A',2,37.5900),(11,23,'SELL','2016-02-29 04:22:53','A',2,37.5900);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolios`
--

DROP TABLE IF EXISTS `portfolios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolios` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `symbol` varchar(6) NOT NULL,
  `shares` int(65) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_id` (`user_id`,`symbol`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolios`
--

LOCK TABLES `portfolios` WRITE;
/*!40000 ALTER TABLE `portfolios` DISABLE KEYS */;
INSERT INTO `portfolios` VALUES (1,1,'GOOG',4),(3,9,'GOOG',2),(8,9,'TSLA',35),(10,9,'M',2),(13,9,'D',3),(15,11,'M',32);
/*!40000 ALTER TABLE `portfolios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `hash` varchar(255) NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'andi','$2y$10$c.e4DK7pVyLT.stmHxgAleWq4yViMmkwKz3x8XCo4b/u3r8g5OTnS',10000.0000),(2,'caesar','$2y$10$0p2dlmu6HnhzEMf9UaUIfuaQP7tFVDMxgFcVs0irhGqhOxt6hJFaa',10000.0000),(3,'eli','$2y$10$COO6EnTVrCPCEddZyWeEJeH9qPCwPkCS0jJpusNiru.XpRN6Jf7HW',10000.0000),(4,'hdan','$2y$10$o9a4ZoHqVkVHSno6j.k34.wC.qzgeQTBHiwa3rpnLq7j2PlPJHo1G',10000.0000),(5,'jason','$2y$10$ci2zwcWLJmSSqyhCnHKUF.AjoysFMvlIb1w4zfmCS7/WaOrmBnLNe',10000.0000),(6,'john','$2y$10$dy.LVhWgoxIQHAgfCStWietGdJCPjnNrxKNRs5twGcMrQvAPPIxSy',10000.0000),(7,'levatich','$2y$10$fBfk7L/QFiplffZdo6etM.096pt4Oyz2imLSp5s8HUAykdLXaz6MK',10000.0000),(8,'rob','$2y$10$3pRWcBbGdAdzdDiVVybKSeFq6C50g80zyPRAxcsh2t5UnwAkG.I.2',10000.0000),(9,'skroob','$2y$10$395b7wODm.o2N7W5UZSXXuXwrC0OtFB17w4VjPnCIn/nvv9e4XUQK',5156.3900),(10,'zamyla','$2y$10$UOaRF0LGOaeHG4oaEkfO4O7vfI34B1W23WqHr9zCpXL68hfQsS3/e',10000.0000),(11,'david','$2y$10$jA4V8s.60QBDhDrTaR75kOQt5Fv99eAy1Eh/9nwVycAVlCKSTdA1C',8610.2400),(12,'mike','$2y$10$EBnnnM.NpK3dYjMyHkPrH.Y2eOxxDh5PpwZu9fXDhUcSojEM87HHG',10000.0000),(13,'test','$2y$10$pxMy5j4ReVMlkUrVCmRe1eHxQ7F73w9/xZcUoQFWHEGfBR7.FK3vy',10000.0000),(14,'steve','$2y$10$qNROemF68FFJ0MUlPTkweu7TL.wHLdISXTTKploNCT9LALAoEhcom',10000.0000),(15,'gary','$2y$10$08.MnyqqVvVQ68r3LBLB7ueAZNaLbrgun/WLu9OzhyNmDoyzN.LBm',10000.0000),(17,'jamie','$2y$10$q1hLOZI1A38OnSAt6DQHDeYzwQDtMpBdHqMwfppKf2Vbn.dAQbsWO',10000.0000),(18,'simon','$2y$10$MXZzEc.7.wbCZKAYnaDlR.QqrrOTFs5H1ZN4bTxnBe2roVU5NDI3q',10000.0000),(19,'halo','$2y$10$cmLT1Bpfxj18TG7Ui/p86eiNspzqL1qW24qo1ifLPlFBNOEOCG4mO',10000.0000),(20,'nicky','$2y$10$LPrCzRMdg2qgHSJS4Ca6J.vl9yWCyjsG3ypc9Shn65YxJ1cUoefQW',10000.0000),(21,'mona','$2y$10$UwAegvw5Qbfxer2Wi0IP2OaJDp5Ste.VH.56ffZ9bcJSVVxtoVs9i',10000.0000),(22,'gio','$2y$10$gqLroaLSxDxncWeWg7pa6umNKUjKCSKNZ7xEENLJDW3WcMr8cOgLq',10000.0000),(23,'ghi','$2y$10$z7K2duU2JmAMX9/yPoB39.UGCLwCXuX0txVDgBknzkrCIgTuYfTni',10000.0000);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-02-29 18:17:27
