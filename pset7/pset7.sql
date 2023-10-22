-- MySQL dump 10.13  Distrib 5.5.40, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.40-0ubuntu0.14.04.1-log

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
  `id` int(10) NOT NULL,
  `num` int(11) NOT NULL AUTO_INCREMENT,
  `type` char(7) COLLATE utf8_unicode_ci NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `symbol` char(4) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(11) NOT NULL,
  `price` decimal(65,4) NOT NULL,
  PRIMARY KEY (`num`)
) ENGINE=InnoDB AUTO_INCREMENT=50 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (0,3,'BUY','2014-11-04 23:42:45','CMG',1,647.6800),(6,4,'BUY','0000-00-00 00:00:00','MSFT',1,47.5700),(6,5,'BUY','0000-00-00 00:00:00','MSFT',1,47.5700),(6,6,'BUY','0000-00-00 00:00:00','MSFT',1,47.5700),(6,7,'BUY','0000-00-00 00:00:00','MSFT',1,47.5700),(6,8,'BUY','0000-00-00 00:00:00','MSFT',1,47.5700),(6,9,'BUY','0000-00-00 00:00:00','HD',1,95.9600),(6,10,'BUY','0000-00-00 00:00:00','MSFT',1,47.5700),(6,11,'BUY','2014-11-05 00:08:20','MSFT',1,47.5700),(6,12,'BUY','2014-11-05 00:09:38','HD',1,95.9600),(6,13,'BUY','2014-11-05 00:16:53','HD',2,95.9600),(6,14,'BUY','2014-11-05 00:22:15','AAPL',2,108.6000),(6,15,'BUY','2014-11-05 00:23:00','MSFT',1,47.5700),(6,16,'BUY','2014-11-05 00:23:50','MSFT',1,47.5700),(6,17,'BUY','2014-11-05 00:24:03','OAK',1,46.8300),(6,18,'BUY','2014-11-05 00:24:20','HD',1,95.9600),(6,19,'BUY','2014-11-05 00:26:22','MSFT',2,47.5700),(6,20,'BUY','2014-11-05 00:30:33','AAPL',1,108.6000),(6,21,'BUY','2014-11-05 00:36:04','HD',1,95.9600),(6,22,'BUY','2014-11-05 00:36:10','MSFT',1,47.5700),(6,23,'SELL','2014-11-05 00:36:19','HD',1,95.9600),(6,24,'SELL','2014-11-05 00:44:54','MSFT',1,47.5700),(6,25,'DEPO','2014-11-05 01:03:16','',0,10000.0000),(6,26,'DEPOSIT','2014-11-05 01:04:02','',0,1000000.0000),(6,27,'DEPOSIT','2014-11-05 01:04:30','-',0,1.0000),(6,28,'DEPOSIT','2014-11-05 01:04:48','-',0,2.0000),(6,29,'BUY','2014-11-05 01:05:19','MSFT',100,47.5700),(6,30,'BUY','2014-11-05 01:21:22','aa',100,16.5600),(6,31,'BUY','2014-11-05 01:21:33','ua',50,64.7900),(6,32,'SELL','2014-11-05 01:25:01','ua',50,64.7900),(6,33,'SELL','2014-11-05 01:26:33','aa',100,16.5600),(6,34,'BUY','2014-11-05 01:30:07','aa',45,16.5600),(6,35,'BUY','2014-11-05 01:30:17','VEEV',250,28.3700),(6,36,'DEPOSIT','2014-11-05 01:40:49','-',0,10.0000),(6,37,'BUY','2014-11-05 01:42:33','aa',1,16.5600),(6,38,'SELL','2014-11-05 01:42:38','aa',46,16.5600),(6,39,'BUY','2014-11-05 01:42:43','aa',3,16.5600),(6,40,'SELL','2014-11-05 01:43:28','aa',3,16.5600),(6,41,'BUY','2014-11-05 01:43:34','aapl',3,108.6000),(6,42,'SELL','2014-11-05 01:44:32','AAPL',3,108.6000),(6,43,'BUY','2014-11-05 01:44:39','aapl',2,108.6000),(6,44,'BUY','2014-11-05 01:45:25','AA',30,16.5600),(6,45,'DEPOSIT','2014-11-05 01:46:36','-',0,10.0000),(6,46,'DEPOSIT','2014-11-05 01:47:30','-',0,0.0010),(6,47,'DEPOSIT','2014-11-05 21:06:31','-',0,10000.0000),(6,48,'DEPOSIT','2014-11-05 21:07:42','-',0,12.0000),(6,49,'BUY','2014-11-06 19:18:12','FREE',10000,0.1549);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolio`
--

DROP TABLE IF EXISTS `portfolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolio` (
  `id` int(10) NOT NULL,
  `symbol` char(4) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(11) NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolio`
--

LOCK TABLES `portfolio` WRITE;
/*!40000 ALTER TABLE `portfolio` DISABLE KEYS */;
INSERT INTO `portfolio` VALUES (6,'AA',30),(6,'AAPL',2),(6,'FREE',10000),(6,'MSFT',100),(6,'VEEV',250);
/*!40000 ALTER TABLE `portfolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'belindazeng','$1$50$oxJEDBo9KDStnrhtnSzir0',10000.0000),(2,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000),(4,'malan','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000),(5,'rob','$1$HA$l5llES7AEaz8ndmSo5Ig41',10000.0000),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',8463.0010),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000),(8,'dan','$1$3GydqlTB$szaR9iOpGDxGWhCWgsY3F/',0.0000),(9,'dan2','$1$i4XQKsBb$f4XX8z0VjzoncsusgmVff.',0.0000),(10,'dan3','$1$5NNIXYGq$WGpJM7zjojhN5Igi5NWK71',0.0000),(11,'dan4','$1$oiXAbc15$fyzvhNBVmOhAJj54ny08f1',0.0000),(12,'dan5','$1$fo9IW4ap$7uln8MRJrOUwQD6KGnni91',0.0000);
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

-- Dump completed on 2014-11-06 14:20:35
