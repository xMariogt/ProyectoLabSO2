from locust import HttpUser, TaskSet, task, between

class UserBehavior(TaskSet):
    @task
    def load_html_pages(self):
        iterations = 5  # Número de veces que se harán las solicitudes para cada página
        
        for _ in range(iterations):
            self.client.get("/web1/home.html")
            self.client.get("/web1/about.html")
            self.client.get("/web1/error.html")
            
            self.client.get("/web2/home.html")
            self.client.get("/web2/about.html")
            self.client.get("/web2/error.html")
            
            self.client.get("/web3/home.html")
            self.client.get("/web3/about.html")
            self.client.get("/web3/error.html")

class HtmlWebsiteUser(HttpUser):
    tasks = [UserBehavior]
    wait_time = between(1, 5)
