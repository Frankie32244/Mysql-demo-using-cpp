drop table if exists workers;
CREATE TABLE `workers` (
  `Id` varchar(12) NOT NULL,
  `_Name` varchar(10) DEFAULT NULL,
  `_Sex` varchar(2) DEFAULT 'm',
  `_Birth` varchar(8) DEFAULT NULL,
  `_time` int(11) DEFAULT '0',
  `_sch` varchar(10) DEFAULT NULL,
  `_work` varchar(20) DEFAULT NULL,
  `_add` varchar(30) DEFAULT NULL,
  `_phone` varchar(12) DEFAULT NULL,
  PRIMARY KEY (Id)
) ENGINE=InnoDB;

INSERT INTO `workers` VALUES ('001', 'A', 'M', '1993.2', '1', 'Bacherlor', 'manual', 'Shanghai', '010-1111111');
INSERT INTO `workers` VALUES ('002', 'B', 'F', '1990.3', '16', 'Bacherlor', 'PM', 'Beijing', '010-1111222');
INSERT INTO `workers` VALUES ('003', 'C', 'M', '1992.2', '1', 'Bacherlor', 'normal', 'Wuhan', '027-1234123');
INSERT INTO `workers` VALUES ('004', 'D', 'F', '1993.1', '3', 'Bacherlor', 'normal', 'Wuhan', '027-1234567');
