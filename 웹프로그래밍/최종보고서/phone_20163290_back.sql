-- MariaDB dump 10.19  Distrib 10.4.21-MariaDB, for Win64 (AMD64)
--
-- Host: localhost    Database: phone
-- ------------------------------------------------------
-- Server version	10.4.21-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `choose`
--

DROP TABLE IF EXISTS `choose`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `choose` (
  `chooseOne` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `choose`
--

LOCK TABLES `choose` WRITE;
/*!40000 ALTER TABLE `choose` DISABLE KEYS */;
/*!40000 ALTER TABLE `choose` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `galaxys21_20163290`
--

DROP TABLE IF EXISTS `galaxys21_20163290`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `galaxys21_20163290` (
  `name` varchar(20) NOT NULL,
  `price` int(11) DEFAULT NULL,
  `save` int(11) DEFAULT NULL,
  `size` varchar(20) DEFAULT NULL,
  `weight` int(11) DEFAULT NULL,
  `display` varchar(20) DEFAULT NULL,
  `wet` varchar(20) DEFAULT NULL,
  `chip` varchar(20) DEFAULT NULL,
  `battery` varchar(20) DEFAULT NULL,
  `batsize` varchar(20) DEFAULT NULL,
  `locked` varchar(50) DEFAULT NULL,
  `charge` varchar(50) DEFAULT NULL,
  `os` varchar(20) DEFAULT NULL,
  `imagelink` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `galaxys21_20163290`
--

LOCK TABLES `galaxys21_20163290` WRITE;
/*!40000 ALTER TABLE `galaxys21_20163290` DISABLE KEYS */;
INSERT INTO `galaxys21_20163290` VALUES ('Galaxy S21',999900,256,'165 X 75 X 8',227,'17.3cm','15m 30minute','Exynos 2100','18 Hours','5000mAh','지문인식 Face ID 패턴 비밀번호','USB TYPE-C','Android','https://img.etnews.com/photonews/2012/1367154_20201218144103_494_0001.jpg');
/*!40000 ALTER TABLE `galaxys21_20163290` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `iphone13_20163290`
--

DROP TABLE IF EXISTS `iphone13_20163290`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `iphone13_20163290` (
  `name` varchar(20) NOT NULL,
  `price` int(11) DEFAULT NULL,
  `save` int(11) DEFAULT NULL,
  `size` varchar(20) DEFAULT NULL,
  `weight` int(11) DEFAULT NULL,
  `display` varchar(20) DEFAULT NULL,
  `wet` varchar(20) DEFAULT NULL,
  `chip` varchar(20) DEFAULT NULL,
  `battery` varchar(20) DEFAULT NULL,
  `batsize` varchar(20) DEFAULT NULL,
  `locked` varchar(50) DEFAULT NULL,
  `charge` varchar(50) DEFAULT NULL,
  `os` varchar(20) DEFAULT NULL,
  `imagelink` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `iphone13_20163290`
--

LOCK TABLES `iphone13_20163290` WRITE;
/*!40000 ALTER TABLE `iphone13_20163290` DISABLE KEYS */;
INSERT INTO `iphone13_20163290` VALUES ('Iphone 13',1090000,256,'131 X 64 X 7',140,'13.7cm','6m 30minute','A15 Bionic CHIP','17 hours','4373mAh','True Depth FACEID 비밀번호','Litening-Cable to USB','IOS 15','https://620880-2015646-raikfcquaxqncofqfm.stackpathdns.com/wp-content/uploads/2021/10/pro-12-1.jpeg');
/*!40000 ALTER TABLE `iphone13_20163290` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-12-24 23:44:42
