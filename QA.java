//Locators
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.edge.EdgeDriver;

public class Main {
    public static void main(String[] args) {
        WebDriver driver = new EdgeDriver();
        driver.manage().window().maximize();
        driver.get("https://www.google.co.uk/");
        System.out.println(driver.getTitle());
        System.out.println(driver.getCurrentUrl());
        driver.findElement(By.id("APjFqb")).sendKeys("Yousef");
        driver.quit();
    }
}



//Form
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.edge.EdgeDriver;

public class Main{
    public static void main(String[] args) {
        WebDriver driver = new EdgeDriver();
        driver.manage().window().maximize();
        driver.get("https://demo.guru99.com/test/login.html");
        System.out.println(driver.getTitle());
        System.out.println(driver.getCurrentUrl());
        driver.findElement(By.xpath("//*[@id=\"email\"]")).sendKeys("yousef@gmail.com");
        driver.findElement(By.xpath("//*[@id=\"passwd\"]")).sendKeys("passwd");
        driver.findElement(By.xpath("//*[@id=\"SubmitLogin\"]")).click();
    }
}


//DropDown
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.edge.EdgeDriver;
import org.openqa.selenium.support.ui.Select;

import java.util.List;

public class Main{
    public static void main(String[] args) {
        WebDriver driver= new EdgeDriver();
        driver.manage().window().maximize();
        driver.get("https://demo.guru99.com/test/newtours/register.php");
        WebElement countryDropDown=driver.findElement(By.name("country"));
        Select countrySelect = new Select(countryDropDown);
        countrySelect.selectByValue("ANGUILLA");
        countrySelect.selectByIndex(2);
        List<WebElement> elementList=countrySelect.getOptions();
        int size= elementList.size();
        for(int i=0;i<size;i++){
            System.out.println(elementList.get(i).getText());
        }
    }
}

//CheckBoxRadio
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.edge.EdgeDriver;

public class Main{
    public static void main(String[] args) {
        WebDriver driver = new EdgeDriver();
        driver.manage().window().maximize();
        driver.get("https://demo.guru99.com/test/radio.html");
        System.out.println(driver.getTitle());
        System.out.println(driver.getCurrentUrl());
        WebElement radio1=driver.findElement(By.id("vfb-7-1"));
        WebElement radio2=driver.findElement(By.id("vfb-7-2"));
        WebElement radio3=driver.findElement(By.id("vfb-7-3"));
        radio3.click();
        WebElement option1=driver.findElement(By.id("vfb-6-0"));
        WebElement option2=driver.findElement(By.id("vfb-6-1"));
        WebElement option3=driver.findElement(By.id("vfb-6-1"));
        option2.click();
        driver.navigate().to("https://demo.guru99.com/test/facebook.html");
        WebElement checkFBpresist= driver.findElement(By.id("persist_box"));
        for (int i=0;i<2;i++){
            checkFBpresist.click();
            System.out.println("CheckBox Presist Status is "+checkFBpresist.isSelected());
        }


    }
}

//Tables
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.edge.EdgeDriver;

public class Tables_51 {
    public static void main(String[] args) {
        WebDriver driver=new EdgeDriver();
        driver.get("https://demo.guru99.com/test/write-xpath-table.html");
        driver.manage().window().maximize();
        WebElement table= driver.findElement(By.xpath("//table/tbody/tr[1]/td[1]"));
        System.out.println(table.getText());

    }
}

//Alerts
import org.openqa.selenium.Alert;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.edge.EdgeDriver;

public class Alerts_6 {
    public static void main(String[] args) {
//        WebDriverManager.edgedriver().setup();
        WebDriver driver=new EdgeDriver();
        driver.get("https://demo.guru99.com/test/delete_customer.php");
        WebElement customerId= driver.findElement(By.name("cusid"));
        customerId.sendKeys("12345");
        WebElement submit=driver.findElement(By.name("submit"));
        submit.click();
        Alert alert1=driver.switchTo().alert();
        System.out.println(alert1.getText());
        alert1.accept();
        Alert alert2=driver.switchTo().alert();
        System.out.println(alert2.getText());
        alert2.accept();
    }
}


//Windows
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.edge.EdgeDriver;

import java.util.Set;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Windows_61 {
    public static void main(String[] args) throws InterruptedException {

        WebDriver driver=new EdgeDriver();
        driver.manage().window().maximize();
        driver.get("https://demo.guru99.com/popup.php");
        String parenWindow=driver.getWindowHandle();
        WebElement clickHere= driver.findElement(By.partialLinkText("Click Here"));
        clickHere.click();
        Set<String> allWindowHandles=driver.getWindowHandles();
        String newTap="";
        for (String s: allWindowHandles){
            if (!parenWindow.equalsIgnoreCase(s)){
                newTap=s;
            }
        }
        Thread.sleep(2000);
        driver.switchTo().window(newTap);
        Thread.sleep(2000);
        driver.switchTo().window(parenWindow);
    }
}


//TestNG

import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.edge.EdgeDriver;
import org.openqa.selenium.ie.InternetExplorerDriver;
import org.testng.Assert;
import org.testng.annotations.*;

public class Hand2 {
    WebDriver driver;

    @BeforeMethod
    @Parameters("browser")
    public void setup(String browser){
        WebDriverManager.edgedriver().setup();
        if(browser.equalsIgnoreCase("Microsoft Edge")){
            driver =new EdgeDriver();
        } else if (browser.equalsIgnoreCase("Internet Explorer")) {
            driver=new InternetExplorerDriver();
        }
        driver.get("https://demo.guru99.com/test/login.html");
        driver.manage().window().maximize();
    }
    @AfterMethod
    public void quit(){
        driver.quit();
    }
    @DataProvider(name = "LoginData")
    public Object[][] getLoginData(){
        return new Object[][]{{"test@gmail.com","Invalid email or password","Invalid"},
                {"test@mail.com","152","https://demo.guru99.com/test/success.html","Calid"}};
    }
    @Test(dataProvider = "LoginData")
    public void f(String UN,String pass, String expected,String CaseType) throws InterruptedException {
        WebElement username=driver.findElement(By.id("email"));
        WebElement password=driver.findElement(By.id("passwd"));
        WebElement loginBtn=driver.findElement(By.id("SubmitLogin"));
        username.sendKeys(UN);
        password.sendKeys(pass);
        loginBtn.submit();
        if(CaseType.equalsIgnoreCase("Valid")){
            Thread.sleep(6000);
            String ActualURL=driver.getCurrentUrl();
            Assert.assertEquals("Valid URL navigation",expected,ActualURL);
        }


    }

}
