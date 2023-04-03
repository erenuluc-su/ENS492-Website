export const getComments = async () => {
  return [
    {
      id: "1",
      body: "First comment",
      username: "deneme",
      userId: "1",
      parentId: null,
      createdAt: "2021-08-16T23:00:33.010+02:00",
      likeCount: 3,
      dislikeCount: 0,
    },
    {
      id: "2",
      body: "Second comment",
      username: "erenu",
      userId: "2",
      parentId: null,
      createdAt: "2021-08-16T23:00:33.010+02:00",
      likeCount: 15,
      dislikeCount: 12,
    },
    {
      id: "3",
      body: "First comment first child",
      username: "erenu",
      userId: "2",
      parentId: "1",
      createdAt: "2021-08-16T23:00:33.010+02:00",
      likeCount: 12,
      dislikeCount: 5,
    },
    {
      id: "4",
      body: "Second comment second child",
      username: "erenu",
      userId: "2",
      parentId: "2",
      createdAt: "2021-08-16T23:00:33.010+02:00",
      likeCount: 43,
      dislikeCount: 5,
    },
  ];
};

export const createComment = async (text, parentId = null) => {
  return {
    id: Math.random().toString(36).substr(2, 9),
    body: text,
    parentId,
    userId: "1",
    username: "deneme",
    createdAt: new Date().toISOString(),
    likeCount: 0,
    dislikeCount: 0,
  };
};

export const updateComment = async (text) => {
  return { text };
};

export const deleteComment = async () => {
  return {};
};