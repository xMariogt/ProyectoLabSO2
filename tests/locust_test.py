from locust import HttpUser, TaskSet, task, between

class UserBehavior(TaskSet):
    @task
    def load_html_pages(self):
        
        self.client.get("/html/web1/home.html")
        self.client.get("/html/web1/about.html")
        self.client.get("/html/web1/error.html")
        
        self.client.get("/html/web2/home.html")
        self.client.get("/html/web2/about.html")
        self.client.get("/html/web2/error.html")
        
        self.client.get("/html/web3/home.html")
        self.client.get("/html/web3/about.html")
        self.client.get("/html/web3/error.html")
        # Agrega aquí las demás rutas a tus archivos HTML

class htmlWebsiteUser(HttpUser):
    tasks = [UserBehavior]
    wait_time = between(1, 5)  # Tiempo de espera entre cada solicitud