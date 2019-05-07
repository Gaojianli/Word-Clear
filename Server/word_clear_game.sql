/*
 Navicat Premium Data Transfer

 Source Server         : Word_clear_game
 Source Server Type    : MySQL
 Source Server Version : 100138
 Source Host           : localhost:3306
 Source Schema         : word_clear_game

 Target Server Type    : MySQL
 Target Server Version : 100138
 File Encoding         : 65001

 Date: 08/05/2019 01:08:25
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for question
-- ----------------------------
DROP TABLE IF EXISTS `question`;
CREATE TABLE `question`  (
  `word` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT 'Word string',
  `level` int(255) NOT NULL DEFAULT 1,
  `committer` int(255) NOT NULL,
  PRIMARY KEY (`word`) USING BTREE,
  INDEX `comitter`(`committer`) USING BTREE,
  INDEX `level`(`level`) USING BTREE,
  CONSTRAINT `comitter` FOREIGN KEY (`committer`) REFERENCES `user` (`id`) ON DELETE CASCADE ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of question
-- ----------------------------
INSERT INTO `question` VALUES ('abandon', 1, 1);
INSERT INTO `question` VALUES ('abruptly', 6, 1);
INSERT INTO `question` VALUES ('acidic', 4, 1);
INSERT INTO `question` VALUES ('administrative', 10, 1);
INSERT INTO `question` VALUES ('affection', 8, 1);
INSERT INTO `question` VALUES ('ahead', 2, 1);
INSERT INTO `question` VALUES ('alert', 2, 1);
INSERT INTO `question` VALUES ('allocate', 4, 1);
INSERT INTO `question` VALUES ('anthocyanin', 8, 1);
INSERT INTO `question` VALUES ('anyone', 4, 1);
INSERT INTO `question` VALUES ('arsenic', 4, 1);
INSERT INTO `question` VALUES ('Asian', 4, 1);
INSERT INTO `question` VALUES ('assembly', 4, 1);
INSERT INTO `question` VALUES ('association', 10, 1);
INSERT INTO `question` VALUES ('assure', 2, 1);
INSERT INTO `question` VALUES ('aviation', 2, 1);
INSERT INTO `question` VALUES ('basalt', 4, 1);
INSERT INTO `question` VALUES ('bean', 2, 1);
INSERT INTO `question` VALUES ('Berlin', 4, 1);
INSERT INTO `question` VALUES ('bias', 2, 1);
INSERT INTO `question` VALUES ('blubber', 4, 1);
INSERT INTO `question` VALUES ('blur', 2, 1);
INSERT INTO `question` VALUES ('bold', 2, 1);
INSERT INTO `question` VALUES ('boule', 4, 1);
INSERT INTO `question` VALUES ('bound', 5, 1);
INSERT INTO `question` VALUES ('buildup', 4, 1);
INSERT INTO `question` VALUES ('buoyant', 6, 1);
INSERT INTO `question` VALUES ('cedar', 2, 1);
INSERT INTO `question` VALUES ('chlorophyll', 10, 1);
INSERT INTO `question` VALUES ('chocolate', 6, 1);
INSERT INTO `question` VALUES ('circumstance', 5, 1);
INSERT INTO `question` VALUES ('civilization', 6, 1);
INSERT INTO `question` VALUES ('cod', 2, 1);
INSERT INTO `question` VALUES ('coexist', 4, 1);
INSERT INTO `question` VALUES ('coil', 2, 1);
INSERT INTO `question` VALUES ('commit', 4, 1);
INSERT INTO `question` VALUES ('committee', 6, 1);
INSERT INTO `question` VALUES ('committer', 1, 1);
INSERT INTO `question` VALUES ('comprehend', 8, 1);
INSERT INTO `question` VALUES ('conclusive', 6, 1);
INSERT INTO `question` VALUES ('conform', 2, 1);
INSERT INTO `question` VALUES ('conjecture', 6, 10);
INSERT INTO `question` VALUES ('contemporary', 8, 1);
INSERT INTO `question` VALUES ('controversy', 6, 1);
INSERT INTO `question` VALUES ('cop', 2, 1);
INSERT INTO `question` VALUES ('core', 3, 1);
INSERT INTO `question` VALUES ('creator', 4, 1);
INSERT INTO `question` VALUES ('darken', 4, 1);
INSERT INTO `question` VALUES ('decompose', 4, 1);
INSERT INTO `question` VALUES ('depress', 6, 1);
INSERT INTO `question` VALUES ('detractor', 6, 1);
INSERT INTO `question` VALUES ('differentiate', 8, 1);
INSERT INTO `question` VALUES ('diffusion', 6, 1);
INSERT INTO `question` VALUES ('diminish', 6, 1);
INSERT INTO `question` VALUES ('dirt', 2, 1);
INSERT INTO `question` VALUES ('disorient', 6, 1);
INSERT INTO `question` VALUES ('domestication', 6, 1);
INSERT INTO `question` VALUES ('dull', 2, 1);
INSERT INTO `question` VALUES ('elder', 2, 1);
INSERT INTO `question` VALUES ('elk', 2, 1);
INSERT INTO `question` VALUES ('enthusiastic', 8, 1);
INSERT INTO `question` VALUES ('Eurasian', 4, 1);
INSERT INTO `question` VALUES ('evaluation', 6, 1);
INSERT INTO `question` VALUES ('false ', 2, 1);
INSERT INTO `question` VALUES ('far-reaching', 6, 1);
INSERT INTO `question` VALUES ('feeder', 4, 1);
INSERT INTO `question` VALUES ('fellow', 2, 1);
INSERT INTO `question` VALUES ('fellowship', 4, 1);
INSERT INTO `question` VALUES ('fetus', 2, 1);
INSERT INTO `question` VALUES ('file', 2, 1);
INSERT INTO `question` VALUES ('fingerboard', 6, 1);
INSERT INTO `question` VALUES ('foodstuff', 6, 1);
INSERT INTO `question` VALUES ('fortunate', 8, 1);
INSERT INTO `question` VALUES ('freudian', 6, 1);
INSERT INTO `question` VALUES ('frontal', 4, 1);
INSERT INTO `question` VALUES ('frustration', 8, 1);
INSERT INTO `question` VALUES ('gut', 2, 1);
INSERT INTO `question` VALUES ('hardship', 4, 1);
INSERT INTO `question` VALUES ('hectare', 4, 1);
INSERT INTO `question` VALUES ('helpful', 2, 1);
INSERT INTO `question` VALUES ('hexagonal', 4, 1);
INSERT INTO `question` VALUES ('historically', 6, 1);
INSERT INTO `question` VALUES ('hobby', 3, 1);
INSERT INTO `question` VALUES ('homestead', 4, 1);
INSERT INTO `question` VALUES ('honeybee', 4, 1);
INSERT INTO `question` VALUES ('huckleberry', 8, 1);
INSERT INTO `question` VALUES ('hypothetical', 10, 1);
INSERT INTO `question` VALUES ('imitative', 4, 1);
INSERT INTO `question` VALUES ('incubate', 4, 1);
INSERT INTO `question` VALUES ('informant', 4, 1);
INSERT INTO `question` VALUES ('infrastructure', 10, 1);
INSERT INTO `question` VALUES ('interglacial', 8, 1);
INSERT INTO `question` VALUES ('jaw', 2, 1);
INSERT INTO `question` VALUES ('journal', 2, 1);
INSERT INTO `question` VALUES ('kinship', 4, 1);
INSERT INTO `question` VALUES ('kneel', 4, 1);
INSERT INTO `question` VALUES ('krypton', 8, 1);
INSERT INTO `question` VALUES ('lamp', 2, 1);
INSERT INTO `question` VALUES ('left-hand', 8, 1);
INSERT INTO `question` VALUES ('lesson', 4, 1);
INSERT INTO `question` VALUES ('linsey-woolsey', 10, 1);
INSERT INTO `question` VALUES ('loosely', 4, 1);
INSERT INTO `question` VALUES ('marble', 4, 1);
INSERT INTO `question` VALUES ('marlin', 4, 1);
INSERT INTO `question` VALUES ('mess', 4, 1);
INSERT INTO `question` VALUES ('middle-class', 8, 1);
INSERT INTO `question` VALUES ('migrant', 4, 1);
INSERT INTO `question` VALUES ('mineralization', 10, 1);
INSERT INTO `question` VALUES ('modification', 8, 1);
INSERT INTO `question` VALUES ('mood', 1, 1);
INSERT INTO `question` VALUES ('moose', 4, 1);
INSERT INTO `question` VALUES ('novelist', 6, 1);
INSERT INTO `question` VALUES ('opaque', 6, 1);
INSERT INTO `question` VALUES ('organizational', 10, 1);
INSERT INTO `question` VALUES ('osprey', 6, 1);
INSERT INTO `question` VALUES ('overirrigation', 10, 1);
INSERT INTO `question` VALUES ('overtime', 6, 1);
INSERT INTO `question` VALUES ('pastoral', 6, 1);
INSERT INTO `question` VALUES ('paxy', 10, 1);
INSERT INTO `question` VALUES ('penicillin', 6, 1);
INSERT INTO `question` VALUES ('pent-up', 4, 1);
INSERT INTO `question` VALUES ('perish', 4, 1);
INSERT INTO `question` VALUES ('personally', 6, 1);
INSERT INTO `question` VALUES ('peruvian', 8, 1);
INSERT INTO `question` VALUES ('photographer', 8, 1);
INSERT INTO `question` VALUES ('pillar', 6, 1);
INSERT INTO `question` VALUES ('pine', 2, 1);
INSERT INTO `question` VALUES ('pixy', 10, 1);
INSERT INTO `question` VALUES ('powder', 2, 1);
INSERT INTO `question` VALUES ('predation', 6, 1);
INSERT INTO `question` VALUES ('presidential', 8, 1);
INSERT INTO `question` VALUES ('prestigious', 6, 1);
INSERT INTO `question` VALUES ('proof', 2, 1);
INSERT INTO `question` VALUES ('qualification', 6, 1);
INSERT INTO `question` VALUES ('radical', 6, 1);
INSERT INTO `question` VALUES ('reasonable', 9, 1);
INSERT INTO `question` VALUES ('refresh', 4, 1);
INSERT INTO `question` VALUES ('reminder', 4, 1);
INSERT INTO `question` VALUES ('renewal', 4, 1);
INSERT INTO `question` VALUES ('replenish', 6, 1);
INSERT INTO `question` VALUES ('reptilian', 6, 1);
INSERT INTO `question` VALUES ('residual', 8, 1);
INSERT INTO `question` VALUES ('restless', 5, 1);
INSERT INTO `question` VALUES ('Russia', 2, 1);
INSERT INTO `question` VALUES ('sailfish', 6, 1);
INSERT INTO `question` VALUES ('satiric', 2, 1);
INSERT INTO `question` VALUES ('Scotland', 6, 1);
INSERT INTO `question` VALUES ('scout', 4, 1);
INSERT INTO `question` VALUES ('senator', 3, 1);
INSERT INTO `question` VALUES ('servant', 10, 1);
INSERT INTO `question` VALUES ('shepherd', 6, 1);
INSERT INTO `question` VALUES ('shine', 2, 1);
INSERT INTO `question` VALUES ('simulate', 4, 1);
INSERT INTO `question` VALUES ('sincere', 2, 1);
INSERT INTO `question` VALUES ('sizable', 2, 1);
INSERT INTO `question` VALUES ('slab', 2, 1);
INSERT INTO `question` VALUES ('slate', 2, 1);
INSERT INTO `question` VALUES ('slick', 2, 1);
INSERT INTO `question` VALUES ('someone', 4, 1);
INSERT INTO `question` VALUES ('sponge', 6, 1);
INSERT INTO `question` VALUES ('spruce', 4, 1);
INSERT INTO `question` VALUES ('starvation', 6, 1);
INSERT INTO `question` VALUES ('static', 4, 1);
INSERT INTO `question` VALUES ('stiffen', 4, 1);
INSERT INTO `question` VALUES ('sting', 7, 1);
INSERT INTO `question` VALUES ('stove', 4, 1);
INSERT INTO `question` VALUES ('suffer', 4, 1);
INSERT INTO `question` VALUES ('surrounding', 5, 1);
INSERT INTO `question` VALUES ('swordfish', 6, 1);
INSERT INTO `question` VALUES ('symbiosis', 6, 1);
INSERT INTO `question` VALUES ('target', 5, 1);
INSERT INTO `question` VALUES ('test', 1, 1);
INSERT INTO `question` VALUES ('timescale', 6, 1);
INSERT INTO `question` VALUES ('tolerant', 4, 1);
INSERT INTO `question` VALUES ('trance', 4, 1);
INSERT INTO `question` VALUES ('tutelage', 6, 1);
INSERT INTO `question` VALUES ('underneath', 8, 1);
INSERT INTO `question` VALUES ('vanish', 2, 1);
INSERT INTO `question` VALUES ('varnish', 4, 1);
INSERT INTO `question` VALUES ('warfare', 4, 1);
INSERT INTO `question` VALUES ('watercraft', 6, 1);
INSERT INTO `question` VALUES ('whenever', 4, 1);
INSERT INTO `question` VALUES ('xenon', 6, 1);

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'User id',
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `isPlayer` tinyint(1) NOT NULL,
  `count` int(11) NOT NULL DEFAULT 0 COMMENT 'passed ranks/committed questions',
  `exp` int(11) NOT NULL DEFAULT 0,
  `level` int(255) NOT NULL DEFAULT 1,
  `session` varchar(33) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `id`(`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 12 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (1, 'committer', '123456', 0, 21, 0, 1, '9fa34da83956f97a2f673169182b660b');
INSERT INTO `user` VALUES (2, 'player', '123456', 1, 28, 290, 3, '65f45ba3d3507af8dce61232190caa4b');
INSERT INTO `user` VALUES (3, '789', '789', 0, 0, 0, 1, NULL);
INSERT INTO `user` VALUES (4, '123', '123', 0, 0, 75, 1, NULL);
INSERT INTO `user` VALUES (5, '345', '345', 1, 0, 0, 1, NULL);
INSERT INTO `user` VALUES (6, 'hhh', '123456', 0, 0, 100, 1, NULL);
INSERT INTO `user` VALUES (8, 'count', 'highest', 1, 0, 0, 1, '2753a1fc01371ab0884038fd6193cf27');
INSERT INTO `user` VALUES (10, 'pixy', 'h19981229', 0, 1, 0, 1, '37c49286b5ecb6b970cf310ce88fbd3c');
INSERT INTO `user` VALUES (11, 'zybshazi', '123', 1, 2, 20, 1, '9291b63731a52e900c062808405f902d');

SET FOREIGN_KEY_CHECKS = 1;
