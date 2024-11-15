
export class TodosModel {
  title: string = "";
  description: string = "";
  id:string;
  constructor(jsonData?: any) {
    if (typeof jsonData == 'object') {
      this.title = jsonData['title'];
      this.description = jsonData['description'];
      if(jsonData['id']){
        this.id = jsonData['id'];
      }
    } else {
      this.title = '';
      this.description = '';
    }
  }
}

// {
//   "created_at": "2024-11-13T16:28:54",
//   "description": "description",
//   "dueDate": "2024-11-14T16:28:54",
//   "id": "41fca04d-0b61-4781-8839-3e36f703189c",
//   "status": "pending",
//   "title": "title",
//   "updated_at": "2024-11-13T16:28:54"
// }
export class GetTodoModel{
  created_at: string;
  description: string;
  dueDate: string;
  id: string;
  status: string;
  title: string;
  updated_at: string;
  constructor(jsonData?: any) {
    if (typeof jsonData == 'object') {
      this.created_at = jsonData['created_at'];
      this.description = jsonData['description'];
      this.dueDate = jsonData['dueDate'];
      this.id = jsonData['id'];
      this.status = jsonData['status'];
      this.title = jsonData['title'];
      this.updated_at = jsonData['updated_at'];
      
    } else {
      this.created_at = '';
      this.description = '';
      this.dueDate = '';
      this.id = '';
      this.status = '';
      this.title = '';
      this.updated_at = '';
    }
  }
}


export class GetTodosModel{
  memberIds: string[];
  members: GetTodoModel[];
  constructor(jsonData?: any) {
    if (typeof jsonData == 'object') {
      this.memberIds = jsonData['memberIds'];
      if(jsonData['members']){
        this.members = jsonData['members'].map((member: any) => new GetTodoModel(member));
      }
    } else {
      this.memberIds = [];
      this.members = [];
    }
  }
}

