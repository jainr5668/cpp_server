export class LoginModel{
  access_token:string;
    token_type: string;

    constructor(jsonData){
        this.access_token = jsonData['access_token'];
        this.token_type = jsonData['token_type'];
    }
}

export class LoginRequestModel{
    username: string;
    password: string;
  
    constructor(jsonData?: any) {
      if (typeof jsonData == 'object') {
        this.username = jsonData['username'];
        this.password = jsonData['password'];
      } else {
        this.username = '';
        this.password = '';
      }
    }
  }
  