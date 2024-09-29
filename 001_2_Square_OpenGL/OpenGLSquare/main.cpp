#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO_Square, VBO_Square, Shader_Square;

//second part to create in this code
// Vertex Shader
static const char* vShader_Square = "							\n\
#version 330													\n\
																\n\
layout(location = 0) in vec3 pos;								\n\
																\n\
void main()														\n\
{															    \n\
	gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0); 	\n\
}																\n\
";

// Fragment Shader
static const char* fShader_Square = "							\n\
#version 330													\n\
																\n\
out vec4 colour_Square;											\n\
																\n\
void main()														\n\
{																\n\
	colour_Square = vec4(1.0, 0.0, 0.0, 1.0);			 		\n\
}																\n\
";
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vShader_Square(Vertex Shader) :																																																					  //
//																																																													  //
//		Bu kod parçası bir vertex shader'ı tanımlar. Vertex shader, her bir vertex'in(noktanın) işlenmesi için kullanılır.İşte bu vertex shader'ın açıklamaları:																					  //
//																																																													  //
//	1-)#version 330									: Shader programının OpenGL 3.3 sürümünü hedeflediğini belirtir.																																  //
//																																																													  //
//	2-)layout(location = 0) in vec3 pos;			: Shader programına gelen vertex pozisyonunu(pos) ve bu pozisyonun 0 numaralı vertex özelliği olduğunu belirtir.																				  //
//																																																													  //
//	3-)void main()									: Shader'ın ana işlevini başlatır.																																								  //
//																																																													  //
//	4-)gl_Position = vec4(pos.x, pos.y, pos.z, 1.0) : Vertex pozisyonunu dört bileşenli bir homojen koordinat olarak gl_Position değişkenine atar.Bu, vertex pozisyonunu 2D veya 3D ekran koordinatlarına dönüştürmek için kullanılır.				  //
//																																																													  //
// fShader_Square(Fragment Shader) :																																																				  //
//																																																													  //
//	Bu kod parçası bir fragment shader'ı tanımlar. Fragment shader, ekranda çizilen her bir pikselin renk değerini belirlemek için kullanılır. İşte bu fragment shader'ın açıklamaları :															  //
//																																																													  //
//	1-)#version 330									: Shader programının OpenGL 3.3 sürümünü hedeflediğini belirtir.																																  //
//																																																													  //
//	2-)out vec4 colour;								: Shader programından çıkan renk değerini(colour) belirtir.																																		  //
//																																																													  //
//	3-)void main()									: Shader'ın ana işlevini başlatır.																																								  //
//																																																													  //
//	4-)colour = vec4(1.0, 0.0, 0.0, 1.0)			: Çıkış renk değerini belirler.Burada, çıkış rengini tamamen kırmızı(R = 1.0, G = 0.0, B = 0.0) olarak ayarlar.Bu, her pikselin kırmızı renkte olduğu anlamına gelir.							  //
//																																																													  //
//																																																													  //
//																																																													  //
//		Bu iki Shader programı, OpenGL programınızın vertex verilerini nasıl işleyeceğini ve hangi renkte çizeceğini tanımlar.Vertex shader, vertex pozisyonlarını dönüştürmek için kullanılırken, fragment shader her pikselin rengini belirler.	  //
//		Bu iki Shader programı birlikte çalışarak bir nesneyi ekrana çizmek için kullanılır.																																						  //
//																																																													  //
// vec3 ve vec4, GLSL(OpenGL Shading Language) dilinde kullanılan veri türleridir ve vektörleri temsil ederler.																																		  //
//																																																													  //
// 1-)vec3											: Bu veri türü, üç bileşenli bir vektörü temsil eder.Genellikle 3D grafiklerde kullanılan pozisyonlar, normal vektörler ve renkler gibi üç bileşenli verileri saklamak için kullanılır.			  //
//														Örneğin, bir vec3 vektörü(x, y, z) bileşenleriyle temsil edilir.																															  //
//																																																													  //
// 2-)vec4											: Bu veri türü, dört bileşenli bir vektörü temsil eder.Genellikle 3D grafiklerde kullanılan pozisyonlar, renkler veya homojen koordinatlar gibi dört bileşenli verileri saklamak için kullanılır. //
//														Örneğin, bir vec4 vektörü(x, y, z, w) bileşenleriyle temsil edilir.																															  //
//																																																													  //
//		Shader programlarında bu veri türleriyle çalışırken, vektörlerin bileşenlerini ve işlemlerini kolayca ifade edebilirsiniz.																													  //
//		 Örneğin, bir vec3 ile iki vektörün çarpımını alabilir veya iki vec4 vektörünü toplayabilirsiniz.																																			  //
//																																																													  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateSquare() //first thing to create while writing the code
{
	GLfloat vertices_of_the_Square[] =
	{
		//first triangle |/
		1.0f, 1.0f, 0.0f, //top right     
		-1.0f, 1.0f, 0.0f, //top left
		-1.0f, -1.0f, 0.0f, //bottom left

		//second triangle /|  
		1.0f, 1.0f, 0.0f, //top right
		-1.0f, -1.0f, 0.0f, //bottom left
		1.0f, -1.0f, 0.0f, //bottom right

		//third triangle /\

		 1.0f, 1.0f, 0.0f, //top right     
		-1.0f, 1.0f, 0.0f, //top left
		 0.0f, 2.0f, 0.0f, //top top
		
		//fourth triangle \/

		-1.0f, -1.0f, 0.0f, //bottom left
		1.0f, -1.0f, 0.0f, //bottom right
		0.0f, -2.0f, 0.0f, //bottom bottom
	};
	//Creating the VAO
	glGenVertexArrays(1, &VAO_Square); // the amounts of values(1 adet vao değeri)| number of vertex array object(VAO) to generate| the storage position of the id of the array
	glBindVertexArray(VAO_Square);

	/*glBindVertexArray işlevi, belirli bir VAO'yu etkinleştirmek veya bağlamak için kullanılır. Bu, belirli bir VAO'nun vertex verilerini kullanmak istediğinizde
	veya çizim işleminizi belirli bir VAO'nun ayarlarına göre yapılandırmak istediğinizde önemlidir. Yani bu işlev, OpenGL'e "Şu anda bu VAO'yu kullanıyorum" 
	demenize yardımcı olur.  Yukarıdaki örnekte, glGenVertexArrays işleviyle bir VAO oluşturulur ve glBindVertexArray işleviyle bu VAO etkinleştirilir. 
	Bu sayede bu VAO üzerinde vertex verilerini ve diğer özellikleri tanımlayabilirsiniz. İşiniz bittiğinde veya başka bir VAO'ya geçmek istediğinizde, 
	glBindVertexArray(0) kullanarak etkin VAO'yu devre dışı bırakabilirsiniz.*/
	
	//Creating the VBO
	
	//Vertex Buffer Object (VBO): Vertex verilerini (örneğin, koordinatlar, renkler ve normal vektörler) saklamak için kullanılır. Bu, 3D modellemeye dayalı 
	//görsel sahnelerde çok önemlidir.
	
	glGenBuffers(1, &VBO_Square); // the amounts of values(1 adet vbo değeri)| number of vertex buffer object(VBO) to generate| the storage position of the id of the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Square); //Bu komut, OpenGL'e "Şu anda işlem yapmak istediğim veri Buffer Object'i bu VBO_Square nesnesidir." demenize yardımcı olur.
	                                           //GL_ARRAY_BUFFER sabit değeri, bu komutun VBO_Square adlı Buffer Object'i Vertex Array Object (VAO) ile ilişkilendireceğini 
											   //belirtir. 
											   // 
											   //GL_ARRAY_BUFFER, vertex verilerini saklamak veya tanımlamak için kullanılan bir tür Buffer Object'i işaret eder.
											   //
											   //VBO_Square, bağlanmak istenen Buffer Object'in adını veya tanımlayıcısını temsil eder. Bu Buffer Object, 
											   //genellikle vertex verilerini içeren bir bellek bloğunu işaret eder.Bu komut kullanıldığında, 
											   //herhangi bir sonraki OpenGL işlemi (örneğin, vertex verilerini yükleme veya çizim komutları) 
											   //VBO_Square adlı Buffer Object'i kullanarak yapılır. Bu, OpenGL'de birden çok Buffer Object'i kullanmanın bir yolunu sağlar,
											   //böylece farklı vertex verilerini veya farklı türde verileri etkili bir şekilde yönetebilirsiniz.
											   //
											   //Özetle, glBindBuffer(GL_ARRAY_BUFFER, VBO_Square); komutu, belirli bir VBO'yu etkinleştirmek veya bağlamak için kullanılır 
											   //ve bu VBO üzerindeki vertex verileri veya diğer verilerle çalışmayı başlatır.

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_of_the_Square), vertices_of_the_Square, GL_STATIC_DRAW); //glBufferData komutu, OpenGL'de belirli bir Buffer Object (genellikle bir Vertex Buffer Object - VBO) ile 
																										   // ilişkilendirilmiş bellekte veri saklamak ve bu veriyi yüklemek için kullanılır. Özellikle GL_ARRAY_BUFFER için kullanıldığında,
																										   // bu komut vertex verilerini saklamak veya güncellemek için kullanılır.
																										   //
                                                                                                           // 	Aşağıda verilen komutun ayrıntılı açıklaması :
                                                                                                           //
                                                                                                           //GL_ARRAY_BUFFER: Bu sabit, işlem yapılacak Buffer Object'in türünü belirtir. 
																										   //	GL_ARRAY_BUFFER, vertex verilerini saklamak ve tanımlamak için kullanılan bir türdür.
                                                                                                           //
                                                                                                           //sizeof(vertices_of_the_Square) : Bu ifade, vertices_of_the_Square adlı veri dizisinin boyutunu belirtir.
																										   // Yani, vertices_of_the_Square dizisinin kaç byte veri içerdiğini hesaplar.Bu, bellekte ne kadar yer ayrılacağını
																										   // belirlemek için kullanılır.
                                                                                                           //	vertices_of_the_Square : Bu, bellekte saklamak istediğiniz veri dizisini temsil eder.
																										   //	 Örneğin, bir kare için vertex verilerini içerebilir.
                                                                                                           //
                                                                                                           //GL_STATIC_DRAW : Bu, OpenGL'e veri kullanım şeklini bildiren bir işaretçidir. 
																										   //	GL_STATIC_DRAW, verinin genellikle bir kez oluşturulup nadiren veya hiç değiştirilmediğini ve bu nedenle 
																										   //	 OpenGL'in bu veriyi optimize etmesi gerektiğini belirtir.Bu tür kullanım, çoğunlukla sabit geometrilerde 
																										   //	 veya nadiren değişen modellerde kullanılır.
                                                                                                           //
                                                                                                           //Bu komut, GL_ARRAY_BUFFER için belirtilen Buffer Object ile vertices_of_the_Square verisini bellekte saklar.
																										   // Bu nedenle, daha sonra çizimlerde veya diğer grafik işlemlerinde bu veriye erişebilirsiniz.Bu işlem, 
																										   // OpenGL'deki vertex verilerini belleğe yükleme ve yönetme sürecinin önemli bir parçasını oluşturur.
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //glVertexAttribPointer komutu, OpenGL'de vertex verilerini Shader programlarına iletmek için kullanılır. 
														   // Bu komut, belirli bir vertex özelliğini (örneğin, pozisyon, renk veya normal) belirler ve bu özelliğin 
														   // nasıl işleneceğini, nerede saklandığını ve nasıl kullanılacağını tanımlar.
                                                           //
                                                           //	Aşağıda verilen komutun ayrıntılı açıklaması :
                                                           //
                                                           //İlk parametre olan 0, vertex özelliğinin indeksini belirtir.Bu indeks, Shader programında tanımlanan in değişkenin
														   // indeksiyle eşleşmelidir.Örneğin, Shader programında in vec3 inPosition; gibi bir değişken tanımlanmışsa, 0 indeksi 
														   // bu değişkeni temsil eder.
                                                           //
                                                           //İkinci parametre olan 3, vertex özelliğinin kaç bileşen içerdiğini belirtir.Bu, örneğin pozisyon bilgisinin 
														   // üç(x, y, z) bileşenden oluştuğunu belirtir.
                                                           //
                                                           //Üçüncü parametre olan GL_FLOAT, vertex özelliğinin bileşenlerinin veri tipini belirtir.Bu örnekte, bileşenlerin 
														   // kayan nokta(float) türünde olduğunu belirtir.
                                                           //
                                                           //Dördüncü parametre olan GL_FALSE, vertex verilerinin normalleştirilip normalleştirilmeyeceğini belirtir.Bu durum, genellikle 
														   // renk veya normal verileri gibi veriler için kullanılır.Bu örnekte, normalleştirme işlemi yapılmayacağını belirtir.
                                                           //
                                                           //Beşinci parametre olan 0, vertex verileri arasındaki adım(stride) değerini belirtir.Bu, vertex verilerinin bellekte sıralı 
														   // olarak saklandığı bir dizi durumda kullanılır.Eğer vertex verileri sıralı ise ve her bir vertex özelliği arasında hiç boşluk 
														   // yoksa, bu değeri 0 olarak belirtebilirsiniz.
                                                           //
                                                           //Altıncı parametre olan 0, vertex verilerinin başlangıç konumunu belirtir.Eğer vertex verileriniz bellekte sıralı olarak saklanıyorsa 
														   // ve verilerin başlangıcı başka bir konumda değilse, bu değeri 0 olarak belirtebilirsiniz.
                                                           //
                                                           //Bu komut, Shader programındaki ilgili vertex özelliğine erişimi tanımlar ve OpenGL'e bu özelliği nasıl işleyeceğini söyler. Bu komutun 
														   // kullanılması, vertex verilerini Shader programına doğru bir şekilde iletmek ve düzgün bir şekilde çizimler yapmak için önemlidir.
	
	glEnableVertexAttribArray(0); //glEnableVertexAttribArray komutu, belirli bir vertex özelliğini (attribute) etkinleştirmek için kullanılır. 
								  // OpenGL'de vertex özellikleri, vertex verilerinin Shader programlarına iletilmesi için kullanılır ve bu 
								  // özelliklerin kullanılabilmesi için etkinleştirilmeleri gerekir.
                                  //
                                  //	Aşağıda verilen komutun ayrıntılı açıklaması :
                                  //
                                  //0 : Bu parametre, etkinleştirilmek istenen vertex özelliğinin indeksini belirtir.
								  // Bu indeks, Shader programındaki in veya attribute değişkenlerinin indeksiyle eşleşmelidir.
								  // Yani, OpenGL'e "Şu anda 0 numaralı vertex özelliğini kullanmak istiyorum." demiş olursunuz.
                                  // "glVertexAttribPointer(0,..." komutundaki 0 ile bağlanır. 
								  //		Örneğin, Shader programınızda aşağıdaki gibi bir vertex özelliği tanımlanmışsa :
                                  //
                                  //			"in vec3 inPosition;"
                                  //		Ve bu özelliği kullanmak istiyorsanız, glEnableVertexAttribArray(0); komutunu kullanarak 
								  //		bu özelliği etkinleştirmeniz gerekecektir.Bu komut, belirli bir vertex özelliğinin çizim 
								  //		sırasında kullanılabilir hale gelmesini sağlar.
                                  //
                                  //Vertex özelliklerini etkinleştirmeniz, Shader programınızın doğru şekilde çalışabilmesi 
								  // ve vertex verilerinin doğru şekilde işlenmesi için önemlidir.Bu komut, belirli bir vertex 
								  // özelliğini etkinleştirmek ve bu özelliği Shader programında kullanılabilir hale getirmek 
								  // için kullanılır.

	glBindBuffer(GL_ARRAY_BUFFER, 0); //1-)glBindBuffer(GL_ARRAY_BUFFER, 0); komutu:
	glBindVertexArray(0);	          //
                                      //Bu komut, mevcut OpenGL bağlamında etkin olan GL_ARRAY_BUFFER türündeki Buffer Object'i 
									  // (genellikle bir Vertex Buffer Object - VBO) devre dışı bırakır. Yani, bu komut ile 
									  // "Şu anki VBO'yu kullanmıyorum." diyorsunuz. Bu, vertex verilerini veya diğer verileri 
									  // yükleme veya düzenleme işlemleri için güvenli bir şekilde sonlandırmak için kullanılır. 
									  // Özellikle, farklı VBO'lar arasında geçiş yaparken veya işlemi tamamladığınızda VBO'nun 
									  // etkisiz hale getirilmesi önemlidir.
                                      //
                                      //2-)glBindVertexArray(0); komutu:
                                      //
                                      //Bu komut, mevcut OpenGL bağlamında etkin olan Vertex Array Object'i (VAO) devre dışı bırakır.
									  // Yani, bu komut ile "Şu anki VAO'yu kullanmıyorum." diyorsunuz. VAO'lar, vertex verilerini ve 
									  // çizim ayarlarını düzenlemek için kullanılır. Bu komut, bir VAO ile ilişkilendirilmiş vertex 
									  // verilerini ve ayarları kullanım sonrası temizlemek ve başka bir VAO'ya geçiş yapmak için kullanılır.
                                      //
                                      //Özetle, bu komutlar, OpenGL programının belirli bir işlemi tamamladığında veya başka 
									  // bir işlem için hazırlandığında mevcut bağlamı temizlemek ve bir sonraki işlem için 
									  // başka bir VBO veya VAO'yu etkinleştirmek için kullanılır. Bu, OpenGL programlarının 
									  // düzenli ve düzgün bir şekilde çalışmasını sağlar ve hataları önler.
									  

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Bu kod, bir OpenGL programında bir kareyi temsil eden vertex verilerini oluşturan ve bu verileri kullanmak üzere bir Vertex Array Object(VAO) ve 																							   //
//		bir Vertex Buffer Object(VBO) oluşturan bir işlevi içerir.İşte bu işlemin her satırının ne yaptığının kısa bir açıklaması :																												   //
//																																																												   //
//		1-)GLfloat vertices_of_the_Square[] = ...																			: Kareyi temsil eden vertex verilerini içeren bir dizi oluşturulur.													   //
//																																																												   //
//		2-)glGenVertexArrays(1, &VAO_Square);																				: Bir VAO oluşturulur ve bu VAO'nun tanımlayıcısı (VAO_Square) elde edilir.											   //
//																																																												   //
//		3-)glBindVertexArray(VAO_Square);																					: Oluşturulan VAO etkinleştirilir.																					   //
//																																																												   //
//			4-)glGenBuffers(1, &VBO_Square);																				: Bir VBO oluşturulur ve bu VBO'nun tanımlayıcısı (VBO_Square) elde edilir.											   //
//																																																												   //
//			5-)glBindBuffer(GL_ARRAY_BUFFER, VBO_Square);																	: Oluşturulan VBO etkinleştirilir ve GL_ARRAY_BUFFER ile ilişkilendirilir.											   //
//																																																												   //
//				6-)glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_of_the_Square), vertices_of_the_Square, GL_STATIC_DRAW);	: VBO'ya vertices_of_the_Square dizisindeki veriler yüklenir. Bu verilerin boyutu ve kullanım amacı belirtilir.		   //
//																																																												   //
//				7-)glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);													: Vertex özellikleri tanımlanır.Bu özellikler, Shader programında kullanılmak üzere belirtilir.						   //
//																															   Bu satır, pozisyon bilgilerini içeren vertices_of_the_Square verilerini 0 numaralı vertex 						   //
//																															   özelliği olarak belirtir.																						   //
//																																																												   //
//				8-)glEnableVertexAttribArray(0);																			: 0 numaralı vertex özelliği etkinleştirilir.Bu, Shader programının bu özelliği kullanabileceğini belirtir.			   //
//																																																												   //
//			9-)glBindBuffer(GL_ARRAY_BUFFER, 0);																			: VBO devre dışı bırakılır.Artık VBO ile ilişkilendirilmiş bir işlem yapmayacağınızı belirtir.						   //
//																																																												   //
//		10-)glBindVertexArray(0);																							: VAO devre dışı bırakılır.Artık VAO ile ilişkilendirilmiş bir işlem yapmayacağınızı belirtir.						   //
//																																																												   //
//	Bu işlev, bir kareyi temsil eden vertex verilerini hazırlar ve bu verileri kullanmak üzere VAO ve VBO oluşturur.																														       //
//		Bu şekilde, bu vertex verileri çizimlerde veya diğer grafik işlemlerinde kullanılmaya hazır hale getirilir.																																   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
//fourth part
void AddShader_Square(GLuint theProgram_Square, const char* shaderCode_Square, GLenum shaderType_Square)
{
	GLuint theShader_Square = glCreateShader(shaderType_Square);

	const GLchar* theCode_Square[1];
	theCode_Square[0] = shaderCode_Square;

	GLint codelenght_Square[1];
	codelenght_Square[0] = strlen(shaderCode_Square);

	glShaderSource(theShader_Square, 1, theCode_Square, codelenght_Square);
	glCompileShader(theShader_Square);
	//this code copied from third part
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader_Square, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader_Square, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType_Square, eLog);
		return;
	}

	glAttachShader(theProgram_Square, theShader_Square);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Bu kod örneği, OpenGL Shader programlarını oluşturmak ve derlemek için kullanılan bir dizi işlevi içerir. (third part and fourth part)																													  //
//	 Bu işlevler, Shader programının bir vertex shader ve bir fragment shader içermesini sağlar. İşte bu kod örneğinin açıklamaları:																														  //
//																																																															  //
//AddShader_Square İşlevi :																																																									  //
//	Bu işlev, Shader programına bir shader eklemek için kullanılır.																																															  //
//	 Ayrıca, bu işlev ile ilgili shader'ın derlenme ve bağlama işlemleri de gerçekleştirilir. 																																								  //
//	 İşte bu işlevin ayrıntılı açıklamaları:																																																				  //
//																																																															  //
//		1-)GLuint theProgram_Square, const char* shaderCode_Square, GLenum shaderType_Square parametreleri															: Shader programının tanımlayıcısı(theProgram_Square), shader kodu(shaderCode_Square) 	  //
//																																									   ve shader türü(shaderType_Square) olarak alınır.										  //
//																																																															  //
//		2-)GLuint theShader_Square = glCreateShader(shaderType_Square);																								: Verilen shader türüne(shaderType_Square) sahip bir shader tanımlayıcısı oluşturulur.	  //
//																																																															  //
//		3-)const GLchar* theCode_Square[1]; theCode_Square[0] = shaderCode_Square; ve GLint codelenght_Square[1]; codelenght_Square[0] = strlen(shaderCode_Square); : Shader kodunu dizi içinde saklar ve kodun uzunluğunu hesaplar.						  //
//																																																															  //
//		4-)glShaderSource(theShader_Square, 1, theCode_Square, codelenght_Square);																					: Shader kodunu shader'a atar.															  //
//																																																															  //
//		5-)glCompileShader(theShader_Square);																														: Shader'ı derler.																		  //
//																																																															  //
//		6-)glGetProgramiv(theShader_Square, GL_COMPILE_STATUS, &result);																							: Shader'ın derleme durumunu kontrol eder.												  //
//																																																															  //
//		7-)if (!result) { ... }																																		: Eğer shader başarılı bir şekilde derlenmezse, hata mesajı yazdırır ve işlevi terk eder. //
//																																																															  //
//		8-)glAttachShader(theProgram_Square, theShader_Square);																										: Shader programına shader'ı ekler.														  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//third part
void CompileShaders_VandF() {
	Shader_Square = glCreateProgram();

	if(!Shader_Square){ 
		printf("Error creating shader program!\n");
		return;
	}

	AddShader_Square(Shader_Square, vShader_Square, GL_VERTEX_SHADER);
	AddShader_Square(Shader_Square, fShader_Square, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(Shader_Square);
	glGetProgramiv(Shader_Square, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(Shader_Square, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}
	
	glValidateProgram(Shader_Square);
	glGetProgramiv(Shader_Square, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(Shader_Square, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CompileShaders_VandF İşlevi :																																															 //
//	Bu işlev, bir Shader programı oluşturur, 																																											 //
//	vertex shader ve fragment shader ekler ve bu Shader programını derler.																																				 //
//		İşte bu işlevin ayrıntılı açıklamaları :																																										 //
//																																																						 //
//		1-)Shader_Square = glCreateProgram();																											: Shader programını oluşturur ve programın tanımlayıcısını alır. //
//																																																						 //
//		2-)AddShader_Square(Shader_Square, vShader_Square, GL_VERTEX_SHADER); ve AddShader_Square(Shader_Square, fShader_Square, GL_FRAGMENT_SHADER);	: Vertex ve fragment shader'ları Shader programına ekler.		 //
//																																																						 //
//		3-)glLinkProgram(Shader_Square);																												: Shader programını bağlar(link) ve hata durumunu kontrol eder.	 //
//																																																						 //
//		4-)glValidateProgram(Shader_Square);																											: Shader programını doğrular ve hata durumunu kontrol eder.		 //
//																																																						 //
// Bu kod örneği, Shader programlarının oluşturulması ve derlenmesi için kullanılan temel işlemleri içerir.Shader programları, //third part ve fourth part için açıklama												 //
// OpenGL'de grafik işlemlerini gerçekleştirmek için kullanılır ve vertex shader ile fragment shader'ı bir araya getirerek 																								 //
// bu işlemleri kontrol ederler.Bu nedenle Shader programlarının doğru bir şekilde oluşturulması ve derlenmesi önemlidir.																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	// Initialise GLFW
	if (!glfwInit()) {
		printf("GLFW Initialisation failed");
		glfwTerminate();
		return 1;
	}
	//Setup GLFW Window Properties
	//OpenGl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// Core Profile = No Backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow Forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "TEST Window", NULL, NULL);
	if (!mainWindow) {
		printf("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}
	//Get Buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	//All modern extension feature
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	//Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	///////Fifth part/////////
	CreateSquare();
	CompileShaders_VandF();

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//	1-)CreateSquare();			: Bu işlev, kareyi temsil eden vertex verilerini ve bu verileri 	//
	//								   OpenGL nesneleriyle(Vertex Array Object - VAO) ilişkilendiren 	//
	//								   işlemleri gerçekleştirir.Kareyi oluşturur ve ilgili OpenGL 		//
	//								   nesnelerini oluşturur.											//
	//																									//
	//	2-)CompileShaders_VandF();  : Bu işlev, Shader programını oluşturur ve bu programda 			//
	//								   kullanılacak vertex shader ve fragment shader'ı belirler. 		//
	//								   Shader programının derleme ve bağlama işlemlerini gerçekleştirir.//
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	

	//Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Get + Handle user Input Events
		glfwPollEvents();

		//clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/////sixth part///
		glUseProgram(Shader_Square);

		glBindVertexArray(VAO_Square);

		glDrawArrays(GL_TRIANGLES, 0, 12);  //!?//

		glBindVertexArray(0);

		glUseProgram(0);
		//////////////////

		glfwSwapBuffers(mainWindow);


		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			// Hata kodunu işleyin veya yazdırın
			printf("OpenGL hatası: %d\n", error);
		}

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Bu bölüm, ana döngünün içeriğini temsil eder ve OpenGL penceresini açık tutarak kullanıcı girişi işler ve kareyi ekranda çizer.																		 //
	//																																																		 //
	//	while (!glfwWindowShouldClose(mainWindow)) { ... }							: Bu döngü, pencere kapatılana kadar uygulamanın çalışmasını sağlar.													 //
	//																																																		 //
	//		1-)glfwPollEvents();													: Bu satır, kullanıcı giriş olaylarını işler ve pencereyi kapatma gibi olayları kontrol eder.							 //
	//																																																		 //
	//		2-)glClearColor(1.0f, 0.0f, 0.0f, 1.0f);								: OpenGL penceresinin temizlenirken kullanılacak temizleme rengini ayarlar.Bu kod, pencereyi kırmızı bir renkle temizler.//
	//																																																		 //
	//		3-)glClear(GL_COLOR_BUFFER_BIT);										: Belirtilen temizleme rengi ile pencereyi temizler.Bu satır, önceki çizimleri temizler ve yeni çizimi başlatır.		 //
	//																																																		 //
	//		4-)glUseProgram(Shader_Square);											: Shader programını etkinleştirir.Bu, belirli bir Shader programının OpenGL tarafından kullanılmasını sağlar.			 //
	//																																																		 //
	//		5-)glBindVertexArray(VAO_Square);										: Kareyi temsil eden VAO'yu etkinleştirir.																				 //
	//																																																		 //
	//		6-)glDrawArrays(GL_TRIANGLES, 0, 4);									: Dikdörtgeni(kareyi) çizer.GL_TRIANGLES çizim modu kullanılarak, belirtilen vertexler ile üçgenler çizilir.			 //
	//																				Bu komut, karenin köşelerini temsil eden vertex verilerini kullanır.													 //
	//																																																		 //
	//		7-)glBindVertexArray(0);												: VAO'yu devre dışı bırakır.																							 //
	//																																																		 //
	//		8-)glUseProgram(0);														: Shader programını devre dışı bırakır.Shader programının kullanılmasının sona erdiğini belirtir.						 //
	//																																																		 //
	//		9-)glfwSwapBuffers(mainWindow);											: Çift tamponlama yöntemi kullanılarak, çizimlerin ekranda gösterilmesini sağlar.										 //
	//																																																		 //
	//			Bu kod parçası, bir OpenGL penceresini oluşturur, bir kareyi kırmızı renkte çizer ve kullanıcı giriş olaylarını işler.																		 //
	//			 Çizim işlemi, belirli bir Shader programı ve vertex verileri ile yapılır.																													 //
	//			 Döngü, pencere kapatılana kadar çalışmaya devam eder ve ekrandaki çizimi günceller.																										 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	return 0;
}