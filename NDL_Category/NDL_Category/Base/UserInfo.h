//
//  UserInfo.h
//  NDL_Category
//
//  Created by dzcx on 2018/6/28.
//  Copyright © 2018年 ndl. All rights reserved.
//

/*
 MARK:数字签名:
 可以识别篡改、伪装、防止抵赖
 数字签名可以识别篡改或者发送者身份是否被伪装，也就是验证消息的完整性，还可以对消息进行认证。还可以防止抵赖。看似一切完美，但是他的弱点也在他的优点上，数字签名需要##用公钥来确认发送者的身份##
 我们需要从一个没有被伪装的发送者那里得到没有被篡改的公钥才行，为了验证得到的公钥是否合法，必须使用公钥证书。##证书是将公钥当做一条消息##，由一个可信的第三方对其签名后所得到的公钥
 
 在数字签名中，有 2 种行为:
 生成消息签名的行为
 验证消息签名的行为
 
 生成消息签名的人是由消息发送者完成的，也称为“对消息签名”。生成签名就是根据消息内容计算数字签名的值
 验证数字签名的人是第三方。第三方验证消息的来源是否属于发送者。验证结果可以是成功，也可以是失败
 
 数字签名对签名密钥和验证密钥进行了区分，使用验证密钥是无法生成签名的。签名密钥只能由签名人持有，而验证密钥则是任何需要验证签名的人都可以持有
 私钥    公钥
 公钥密钥    接收者解密时使用    发送者加密时使用
 数字签名    签名者生成签名时使用    验证者验证签名时使用
 谁持有密钥？    个人持有    只要需要，任何人都可以持有
 
 ##RSA 算法中公钥加密和数字签名正好是完全相反的关系##
 
 有两种生成和验证数字签名的方法:
 直接对消息签名的方法
 对消息的散列值签名的方法
 一般都会使用第 2 种方法。原因是因为第 1 种方法要对整个消息进行加密，而且是公钥密钥算法，非常耗时。利用简短的单向散列函数来替代消息本身。再进行加密(对消息进行签名)，会快很多
 
 数字签名是利用了 “没有私钥的人就无法生成使用该私钥所生成的密文” 这一性质来实现的。生成的密文并非是用于保证机密性，而是用于代表一种只有持有该密钥的人才能生成的信息。所以私钥产生的密文是一种认证符号(authenticator)
 数字签名本来就不保证消息的机密性.如果需要保证机密性，可以考虑加密和数字签名结合起来使用
 
 对明文消息所施加的签名，一般称为明文签名(clearsign)
 
 验证数字签名的时候需要合法的公钥，但是如何才能知道自己拿到的公钥是合法的呢？这个时候就需要把公钥作为信息，对它加上数字签名，得到公钥证书
 
 SSL/TLS 在认证服务器身份的时候会使用服务器证书，服务器证书就是加上了数字签名的服务器公钥
 
 mod 求余
 
 用 RSA 生成签名
 签名 = 消息^D mod N (用 RSA 生成签名)
 上面的 D 和 N 就是签名者的私钥。签名就是对消息的 D 次方求 mod N 的结果
 
 用 RSA 验证签名
 由签名求得的消息 = 签名^E mod N (用 RSA 验证签名)
 上面的 E 和 N 就是签名者的公钥。验证者计算签名的 E 次方并求 mod N，得到“由签名求得的消息”。将这个消息和发送者直接发过来的消息进行对比，如果一致就验证成功，不一致就验证失败
 
 其他几种数字签名:
 ElGamal
 DSA(Digital Signature Algorithm)
 ECDSA(Elliptic Curve Digital Signature Algorithm)
 Rabin
 
 ###数字签名需要用公钥来确认发送者的身份###
 
 ##公钥密码和数字签名使用不同的密钥对##
 
 OpenSSL 中的 RSA 数字签名:
 和 RSA 公钥加密不一样，RSA 实现的数字签名技术需要涉及到摘要计算，所以需要指定 一个 Hash 算法
 
 // 生成一个 RSA 密钥对，密钥长度 1024 长度
 $ openssl genrsa -out rsaprivatekey.pem 1024
 // 从密钥对中分离出公钥
 $ openssl rsa -in rsaprivatekey.pem -pubout -out rsapublickey.pem
 // 生成签名文件
 // 对 plain.txt 文件使用 sha256 Hash 算法和签名算法生成签名文件 signature.txt
 $ echo "hello" >> plain.txt
 $ openssl dgst -sha256 -sign rsaprivatekey.pem -out signature.txt plain.txt
 // 校验签名文件
 // 用相同的摘要算法和签名算法校验签名文件，需要对比签名文件和原始文件
 $ openssl dgst -sha256 -verify rsapublickey.pem -signature signature.txt plain.txt
 
 */

#import <Foundation/Foundation.h>

@interface UserInfo : NSObject

SINGLETON_FOR_HEADER(UserInfo)

@property (nonatomic, assign) long long userID;// 用户ID

@property (nonatomic, copy) NSString *token;// 用户登录后分配的登录Token

@end

/*
 MARK:公钥证书:
 我们需要从一个没有被伪装的发送者那里得到没有被篡改的公钥才行，为了验证得到的公钥是否合法，必须使用公钥证书。证书是将公钥当做一条消息，由一个可信的第三方对其签名后所得到的公钥
 公钥证书(Public-Key Certificate，PKC)记录着个人信息(姓名、组织、邮箱地址等个人信息)和个人公钥，并由认证机构(Certification Authority、Certifying Authority，CA)施加数字签名。公钥证书也简称为证书(certificate)
 
 Alice 向 Bob 发送密文的场景，在生成密文时所使用的 Bob 的公钥是通过认证机构获取的
 Bob 的密钥可以是自己生成的，也可以由认证机构代为生成
 认证机构在拿到 Bob 的公钥以后会开始认证这个公钥是否是 Bob 的。有三种验证等级，Class 1 通过邮箱中的邮件进行确认本人身份；Class 2 通过第三方数据库来确认本人身份；Class 3 通过当面认证和身份来确认本人身份。等级越高，身份认证越严格
 Alice 使用认证机构 Trent 的公钥对证书中的数字签名进行验证，如果验证成功，就确认了证书中所包含的公钥是 Bob 的
 
 公钥基础设施(Public-Key Infrastructure)是为了能够更有效的运用公钥而制定的一系列规范和规格的总称。英文缩写 PKI
 RSA 公司制定的 PKCS(Public-Key Cryptography Standards，公钥密码标准)系列规范也是 PKI 的一种，互联网规格 RFC(Request for Comments)也是 PKI 的一种，X.509 也是 PKI 的一种
 
 ##认证机构只要对公钥进行数字签名就可以了，所以任何人都可以成为认证机构##
 
 PKI 的组成要素:
 用户——使用 PKI 的人
 认证机构——颁发证书的人
 仓库——保存证书的数据库
 
 类似 Bob 注册公钥的用户:
 生成密钥对(可以自己生成也可以由认证机构生成)
 在认证机构注册公钥
 向认证机构申请证书
 申请作废已注册的证书
 解密收到的密文
 对消息进行数字签名
 类似 Alice 使用公钥的用户:
 将消息加密后发送给接收者
 验证数字签名
 
 认证机构 CA:
 认证机构(Certification Authority，CA)是对证书进行管理的人。主要负责以下操作：
 
 生成密钥对(也可以由用户生成)
 对注册公钥的人进行身份认证
 生成并颁发证书
 作废证书
 
 认证机构中还可以细分一个注册机构(Registration Authority，RA)，注册机构专门处理注册相关的业务，认证机构专门颁发证书和作废证书
 
 仓库:
 仓库(repository)是一个保存证书的数据库。仓库也叫证书目录。作废的证书也需要制作一张证书作废清单(Certificate Revocation List，CRL)
 
 证书链:
 证书也可以具有层次结构，例如顶级根 CA 颁发的证书，到下一级 CA 颁发的证书，这样一级一级形成层次
 
 ###证书实际上使用的就是数字签名技术###
 
 有一个机构叫 PKG (Private Key Generator，私钥生成机构)，这个机构和认证机构 CA 地位并列。它利用一些公开的信息，邮箱，通信地址，姓名，这些基于 ID 的密码来生成私钥。它所依赖的是对 ID 的信任。私钥生成机构负责根据 ID 生成私钥，并将私钥安全的发送给合法的接收者。由于私钥生成机构拥有对所有密文的解密权限，所以自身的安全性需要更加注意
 */
